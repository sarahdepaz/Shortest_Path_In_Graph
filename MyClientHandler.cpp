
#include "MyClientHandler.h"

/**
 * Handle the client we connected with.
 * @param socket_id The socket we connected through.
 */
void MyClientHandler::handleClient(int socket_id) {
  /* Hold's the parameters we need for solver. */
  std::string data;
  std::string maze;
  std::string start_pos;
  std::string goal_pos;
  /* Reading from client. */
  data = Read(socket_id);
  if (data.empty()) {
    close(socket_id);
    return;
  }

  /* Parsing data */
  std::string line;
  std::istringstream string_stream;
  string_stream.str(data);
  std::vector<std::string> lines;

  while (std::getline(string_stream, line)) {
    lines.push_back(line);
  }

  goal_pos = lines.back();
  lines.pop_back();
  start_pos = lines.back();
  lines.pop_back();

  auto iterator = lines.begin();
  for (; iterator < lines.end(); ++iterator) {
    maze += (*iterator) + "\n";
  }
  maze.pop_back();

  /* Getting hash codes for values. */
  std::size_t matrix_hash = GetHashOfString(maze);
  std::size_t start_pos_hash = GetHashOfString(start_pos);
  std::size_t goal_pos_hash = GetHashOfString(goal_pos);

  /* The string representing the problem. */
  std::string problem_text = std::to_string(matrix_hash) +
      "," +
      std::to_string(start_pos_hash) +
      "," +
      std::to_string(goal_pos_hash);

  mutex.lock(); /* Locking mutex. */

  std::string result;
  if (this->cacheManager->isSolutionExists(problem_text)) {
    result = this->cacheManager->getSolution(problem_text);
  } else {
    // Solving and saving.
    try {

      /* Creates searcher as a solver. */
      ISearcher<std::pair<int, int>, State<std::pair<int, int>> *> *searcher;
      searcher = new BestFirstSearch<std::pair<int, int>, State<std::pair<int, int>> *>;
      Solver<ISearchable<std::pair<int, int>> *, State<std::pair<int, int>> *> *solver
          = new SolverToSearcherAdapter(searcher);

      ISearchable<std::pair<int, int>> *searchable = new SearchableMatrix(maze, start_pos, goal_pos);
      State<std::pair<int, int>> *path = solver->solveProblem(searchable);

      //State<std::pair<int,int>>* path = this->solver->solveProblem(searchable);
      result = GetPath(path);

      /* Deleting saved data. */
      delete (searchable);
      delete (solver);
      delete (searcher);

      // Saving.
      this->cacheManager->saveSolution(problem_text, result);

    } catch (std::exception &e) {
      //perror("Search failure.\n");
      mutex.unlock();
      close(socket_id);
      return;
    }
  }
  mutex.unlock(); /* Unlock mutex. */

  // Writing solution.
  result += '\n';
  int n = send(socket_id, result.c_str(), (result.length()), 0);

  if (n < 0) {
    //perror("ERROR writing to socket");
    close(socket_id);
    return;
  }

  close(socket_id);
}

/**
 * Get solution and parse it to string of directions.
 * @param pathEnd The last State in the path.
 * @return string of directions.
 */
std::string MyClientHandler::GetPath(State<std::pair<int, int>> *pathEnd) {

  State<std::pair<int, int>> *current = pathEnd;
  State<std::pair<int, int>> *previous = current->getCameFrom();
  std::string result;
  while (previous != nullptr) {
    std::pair<int, int> current_pos = current->getState();
    std::pair<int, int> previous_pos = previous->getState();
    // Changed to capital letters to match output
    // todo need to add vertices
    if (current_pos.first == previous_pos.first + 1) {
      result.insert(0, ",Down (" + std::to_string((int)current->getTotal_cost_to())+")");
    } else if (current_pos.first == previous_pos.first - 1) {
      result.insert(0, ",Up (" + std::to_string((int)current->getTotal_cost_to())+")");
    } else if (current_pos.second == previous_pos.second - 1) {
      result.insert(0, ",Left (" + std::to_string((int)current->getTotal_cost_to())+")");
    } else if (current_pos.second == previous_pos.second + 1) {
      result.insert(0, ",Right (" +std::to_string((int)current->getTotal_cost_to())+")");
    }
    current = previous;
    previous = current->getCameFrom();
  }
  result.erase(0, 1);

  return result;
}

/**
 * Read's data from client.
 * @param socket_id The socket we connected to.
 * @return string - The data we got.
 */
std::string MyClientHandler::Read(int socket_id) {

  bool isEndReached = false;
  char buffer[1024];
  int number_of_bytes_read;
  std::string all_data;
  std::string actual_data;
  std::string data_read;

  while (!isEndReached) {
    /* Clear buffer. */
    bzero(buffer, 1024);
    number_of_bytes_read = (int) read(socket_id, buffer, 1023);

    /* Check for reading failure. */
    if (number_of_bytes_read < 0) {
      return "";
    }

    data_read = buffer;
    all_data += data_read;

    /* Checking for end of message code. */
    if (data_read.find("end") != std::string::npos) {

      /* Stopping the reading process. */
      isEndReached = true;
    }
  }
  actual_data = all_data.substr(0, all_data.find("end"));
  actual_data.erase(std::remove(actual_data.begin(), actual_data.end(), '\r'), actual_data.end());
  return actual_data;

}

/**
 * Returns hash of a string.
 * @param str The string to get hash for.
 * @return The hash value.
 */
std::size_t MyClientHandler::GetHashOfString(std::string str) {
  return std::hash<std::string>{}(str);
}

//ClientHandler *MyClientHandler::clone() {
//  ClientHandler *c = new MyClientHandler(solver->clone(), cacheManager);
//  return c;
//}

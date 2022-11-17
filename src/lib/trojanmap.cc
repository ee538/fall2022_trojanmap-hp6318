#include "trojanmap.h"
#include <iostream> 

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return
 * -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string &id) {
  if (data.find(id)==data.end()){
    return -1;
  }
  else {
    return data[id].lat;
  }
   
  return 0;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist,
 * return -1.
 *
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string &id) {
  if (data.find(id)==data.end()){
    return -1;
  }
  else {
    return data[id].lon;
  }
   
  return 0;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return
 * "NULL".
 *
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string &id) {
  if (data.find(id)==data.end()){
    return "NULL";
  }
  else {
    return data[id].name;
  }
 
  return "";
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return
 * an empty vector.
 *
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string &id) {
  if (data.find(id)==data.end()){
    return {};
  }
  else {
    return data[id].neighbors;
  }
   
  return {};
}

/**
 * GetID: Given a location name, return the id.
 * If the node does not exist, return an empty string.
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string &name) {
  std::string res = "";
  auto temp=name;
  std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  for (auto it:data){
    std::transform(it.second.name.begin(), it.second.name.end(), it.second.name.begin(), ::tolower);
    if (it.second.name==temp){
      res=it.second.id;
      break;
    }
  }
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not
 * exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  for (auto it:data){
    std::transform(it.second.name.begin(), it.second.name.end(), it.second.name.begin(), ::tolower);
    if (it.second.name==name){
      results.first=it.second.lat;
      results.second=it.second.lon;
    }
  }
  return results;
}

/**
 * CalculateEditDistance: Calculate edit distance between two location names
 *
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b) {     
  std::transform(a.begin(), a.end(), a.begin(), ::tolower);
  std::transform(b.begin(), b.end(), b.begin(), ::tolower);
  if (a==b){
    return 0;
  }
  int m = a.size(); //rows
  int n = b.size(); //cols
  std::vector<std::vector<int>>dp_mat(m+1,std::vector<int>(n+1,0));
  //first row
  for (int i=0;i<=n;i++){
    dp_mat[0][i]=i;
  }
  //first col
  for (int i=1;i<=m;i++){
    dp_mat[i][0]=i;
  }
  for (int i=1;i<=m;i++){
    for (int j=1;j<=n;j++){
      if (a[i-1]==b[j-1]){
        dp_mat[i][j]=dp_mat[i-1][j-1];
      }
      else{
        dp_mat[i][j]=1+std::min(dp_mat[i-1][j],std::min(dp_mat[i-1][j-1],dp_mat[i][j-1]));
      }
    }
  }

  return dp_mat[m][n];
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit
 * distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string tmp = ""; // Start with a dummy word
  int min_dis=1000;
  int temp;
  for (auto it:data){
    temp=TrojanMap::CalculateEditDistance(name,it.second.name);
    if (temp<min_dis){
      tmp=it.second.name;
      min_dis=temp;
    }
    if (min_dis==0){
      break;
    }
  }
  return tmp;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name) {
  std::vector<std::string> results;
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  int inp_size=name.size();
  for (auto it:data){
    auto temp=it.second.name.substr(0,inp_size);
    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    if (temp==name){
      results.push_back(it.second.name);
    }
  }
  return results;
}

/**
 * GetAllCategories: Return all the possible unique location categories, i.e.
 * there should be no duplicates in the output.
 *
 * @return {std::vector<std::string>}  : all unique location categories
 */
std::vector<std::string> TrojanMap::GetAllCategories() {
  std::vector<std::string>result;
  std::set<std::string>unique;
  for (auto it:data){
    for (auto cat:it.second.attributes){
      unique.insert(cat);
    }
  }
  for (auto ele:unique){
    result.push_back(ele);
  }
  return result;
}

/**
 * GetAllLocationsFromCategory: Return all the locations of the input category (i.e.
 * 'attributes' in data.csv). If there is no location of that category, return
 * (-1, -1). The function should be case-insensitive.
 *
 * @param  {std::string} category          : category name (attribute)
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetAllLocationsFromCategory(
    std::string category) {
  std::vector<std::string> res;
  std::transform(category.begin(), category.end(), category.begin(), ::tolower);
  for (auto it:data){
    if (it.second.attributes.find(category)!=it.second.attributes.end()){
      //found
      res.push_back(it.first);
    }
  }
  return res;
}

/**
 * GetLocationRegex: Given the regular expression of a location's name, your
 * program should first check whether the regular expression is valid, and if so
 * it returns all locations that match that regular expression.
 *
 * @param  {std::regex} location name      : the regular expression of location
 * names
 * @return {std::vector<std::string>}     : ids
 */
std::vector<std::string> TrojanMap::GetLocationRegex(std::regex location) {
  std::vector<std::string> results;
  try {
    //  std::regex myregex ("*");
    //location;
  } catch (std::regex_error& e) {
     return {};
  }
  for (auto & it:data){
    if (std::regex_match (it.second.name,location)){
      results.push_back(it.first);
    }
  }
  return results;
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 *
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id,
                                    const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) *
                                           cos(b.lat * M_PI / 180.0) *
                                           pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(std::min(1.0, sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations
 * inside the vector.
 *
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0; i < int(path.size()) - 1; i++) {
    sum += CalculateDistance(path[i], path[i + 1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path
 * which is a list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  
  std::string src_id=TrojanMap::GetID(location1_name);
  std::string dst_id=TrojanMap::GetID(location2_name);
  

  // std::priority_queue<std::pair<double,std::string>> pq; //(updated_distance,node_id)
  // std::unordered_map<std::string,std::pair<double,std::vector<std::string>>> dis_path; //node_id:(updated_distance,updated_path)
  // std::set<std::string> visited; //store the nodes visited
  
  // std::pair<std::string,std::pair<double,std::vector<std::string>>> initial;
  // initial.first=src_id;
  // initial.second.first=0;
  // initial.second.second={};

  // pq.push(std::make_pair(0,src_id));
  
  // while (!pq.empty()){
  //   auto curr=pq.top(); //extract the node with minimum distance among the queue
  //   pq.pop();
  //   if (curr.second==dst_id){
  //     break;
  //   } 
  //   if (visited.find(curr.second)==visited.end()){ //poped node is not visited
  //     visited.insert(curr.second); //make this node visited
  //     for (auto &neighbor:data[curr.second].neighbors){ //visit only those neighbors who are yet to be visited
  //       if (visited.find(neighbor)==visited.end()){
  //         //add the distance of previous path + dist between node & neighbor
  //         double new_dist=dis_path[curr.second].first+ TrojanMap::CalculateDistance(curr.second,neighbor);
  //         if (dis_path.find(neighbor)!=dis_path.end()){
  //           //check for relaxation, if yes, update distance and path and add neighbor to queue
  //           if (dis_path[neighbor].first>new_dist){
  //             dis_path[neighbor].first=new_dist;
  //             std::vector<std::string> new_path=dis_path[curr.second].second;
  //             new_path.push_back(curr.second);
  //             dis_path[neighbor].second=new_path;
  //             pq.push(std::make_pair(-new_dist,neighbor));
  //           }
  //         }
  //         else{
  //           //neighbor distance is infinity till now
  //           std::pair<std::string,std::pair<double,std::vector<std::string>>> neighbor_new;
  //           neighbor_new.first=neighbor;
  //           neighbor_new.second.first=new_dist;
  //           std::vector<std::string> new_path=dis_path[curr.second].second;
  //           new_path.push_back(curr.second);
  //           neighbor_new.second.second=new_path;
  //           dis_path.insert(neighbor_new);
  //           pq.push(std::make_pair(-new_dist,neighbor));
  //         }
  //       }
  //     }
  //   }
  // }
  
  std::vector<std::string> result;
  // if (dis_path.find(dst_id)!=dis_path.end()){
  //   //found the shortest path
  //   result=dis_path[dst_id].second;
  //   result.push_back(dst_id);
  // }
  return result;
}


/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest
 * path which is a list of id. Hint: Do the early termination when there is no
 * change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(std::string location1_name, std::string location2_name) {
  std::string src_id=TrojanMap::GetID(location1_name);
  std::string dst_id=TrojanMap::GetID(location2_name);
  
  // std::unordered_map<std::string,std::vector<std::string>> path_map={{src_id,{}}}; //to store the paths
  // std::unordered_map<std::string,double>val; //current iteration distance update 
  // std::unordered_map<std::string,double>prev={{src_id,0}}; //previous iteration distan path;
  
  // bool change_flag=true; //to track the changes in prev & val 
  // double temp;
  // while (change_flag){
  //   for (auto &node:prev){
  //     for (auto &neighbor:data[node.first].neighbors){
  //       if (val.find(neighbor)==val.end()){
  //         val[neighbor]=INT_MAX;
  //       }
  //       if (prev.find(neighbor)==prev.end()){
  //         temp=INT_MAX;
  //       }
  //       else{
  //         temp=prev[neighbor];
  //       }
  //       double new_dist=prev[node.first]+TrojanMap::CalculateDistance(node.first,neighbor);
  //       val[neighbor]=std::min(val[neighbor],std::min(temp,new_dist));
  //       if (val[neighbor]==new_dist){
  //         //relaxation, update path
  //         std::vector<std::string>new_path=path_map[node.first];
  //         new_path.push_back(node.first);
  //         if (path_map.find(neighbor)==path_map.end()){
  //           path_map.insert(std::make_pair(neighbor,new_path));
  //         }
  //         else{
  //           path_map[neighbor]=new_path;
  //         }
  //       }
  //     }
  //   }
  //   //check for changes
  //   if (val==prev){
  //     change_flag=false;
  //   }
  //   else{
  //     prev=val;
  //   }
  // }
  std::vector<std::string> path;
  // if (path_map.find(dst_id)!=path_map.end()){
  //   //path found
  //   path=path_map[dst_id];
  //   path.push_back(dst_id);
  // }
  
  return path;
}

/**
 * Traveling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

// Hint: https://en.wikipedia.org/wiki/2-opt
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravelingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(
    std::string locations_filename) {
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, word)) {
    location_names_from_csv.push_back(word);
  }
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(
    std::string dependencies_filename) {
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;
  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::vector<std::string> dependency;
    while (getline(s, word, ',')) {
      dependency.push_back(word);
    }
    dependencies_from_csv.push_back(dependency);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a
 * sorting of nodes that satisfies the given dependencies. If there is no way to
 * do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     :
 * prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(
    std::vector<std::string> &locations,
    std::vector<std::vector<std::string>> &dependencies) {
  std::vector<std::string> result;
  std::unordered_map<std::string,int>in_degrees;
  std::unordered_map<std::string,std::vector<std::string>>parent;
  
  for (auto &node:locations){
    in_degrees.insert({node,0});
    parent.insert({node,{}});
  }

  for (auto &edges:dependencies){
    in_degrees[edges[1]]+=1;
    parent[edges[0]].push_back(edges[1]);
  }
  
  std::queue<std::string>q; //bfs 

  for (auto &root:in_degrees){
    if (root.second==0){
      // add the starting place which has no dependecy
      q.push(root.first);
    }
  }

  if (q.size()==0){
    // no path possible, cycle detected
    return result; //empty
  }

  while (q.size()!=0){
    auto curr=q.front();
    q.pop();
    result.push_back(curr);
    for (auto child:parent[curr]){
      in_degrees[child]-=1;
      if (in_degrees[child]==0){
        q.push(child);
      }
    }
  }
  if (result.size()==locations.size()){
    return result;
  }
  return {};     
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  // left-lon, right-lon, upper-lat, and lower-lat bounds
  double temp_lat=data[id].lat;
  double temp_long=data[id].lon;
  if ((temp_lat<square[2] && temp_lat>square[3]) && (temp_long<square[1] && temp_long>square[0])){
    return true;
  }
  return false;
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location
 * ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square
 * area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the
 * square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  for (auto it:data){
    if (TrojanMap::inSquare(it.first, square)){
      subgraph.push_back(it.first);
    }
  }
  return subgraph;
}

/**
 * Cycle Detection: DFS helper function for cycle detection
 *
 * @param {std::string} node : current node id
 * @param {std::set<std::string>} visited: set of nodes visited of subgraph
 * @param {std::string} parent : current node'parent id
 * @param {std::vector<double>} square: upper,lower,left,right bounds of subgraph
 * @return {bool}: whether there is a cycle or not in this graph/region of subgraph
 */

bool TrojanMap::detection_helper(std::string &node,std::set<std::string>& visited,std::string& parent,std::vector<double> &square){
  //mark current visited
  visited.insert(node);

  //run dfs on node's neighbor
  for (auto neighbor:data[node].neighbors){
    //check neighbor in square
    if (TrojanMap::inSquare(neighbor, square)){
      //check neighbor not visited
      if (visited.find(neighbor)==visited.end()){
        if (TrojanMap::detection_helper(neighbor,visited,node,square)){
          return true;
        }
      }
      else{
        //already neighbor was visited
        if (neighbor!=parent){
          return true;
        }
      }
    }
  }
  return false;
}


/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true
 * if there is a cycle path inside the square, false otherwise.
 *
 * @param {std::vector<std::string>} subgraph: list of location ids in the
 * square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  std::set<std::string>visited;
  std::string temp_parent="None";
  for (auto node:subgraph){
    if (visited.find(node)==visited.end()){
      //dfs on each unvisited node 
      if (TrojanMap::detection_helper(node,visited,temp_parent,square)){
        //cycle detected
        // // path remaining to be plotted
        return true;
      }
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r,
 * find all locations in class C on the map near L with the range of r and
 * return a vector of string ids
 *
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {

  //filter out the locations based on the attribute name
  std::vector<std::string> filtered_loc= TrojanMap::GetAllLocationsFromCategory(attributesName);
  
  //maintain a priority queue(max_heap) of length k
  std::priority_queue<std::pair<double,std::string>> pq; //max-heap 
  
  std::string center_id=TrojanMap::GetID(name);

  double temp_dis;

  for (auto near_loc:filtered_loc){
    if (near_loc!=center_id){
      temp_dis=TrojanMap::CalculateDistance(near_loc,center_id);
      if (temp_dis<=r) {
        //within radius
        if (pq.size()<=k){
          pq.push(std::make_pair(temp_dis,near_loc));
        }
        else{
          if (pq.top().first>temp_dis){
            pq.pop();
            pq.push(std::make_pair(temp_dis,near_loc));
          }
        }
      }
    }
  }
  std::vector<std::string> res(pq.size());
  for (int i=pq.size()-1;i>=0;i--){
    res[i]=pq.top().second;
    pq.pop();
  }
  return res;
}

/**
 * Shortest Path to Visit All Nodes: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of
 * total distance and the all the progress to get final path
 */
std::vector<std::string> TrojanMap::TrojanPath(
      std::vector<std::string> &location_names) {
    std::vector<std::string> res;
    return res;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 *
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0])) n.attributes.insert(word);
        if (isdigit(word[0])) n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

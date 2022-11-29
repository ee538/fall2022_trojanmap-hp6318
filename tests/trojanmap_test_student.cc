#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"
#include <vector>
#include <unordered_set>


// Phase 1
// Test Autocomplete function
TEST(TrojanMapStudentTest, Autocomplete_1) {
  TrojanMap m;
  // Test the simple case
  auto names = m.Autocomplete("Ra");
  std::unordered_set<std::string> gt = {"Ralphs", "Ramen KenJo"}; // groundtruth for "Ch"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower case
  names = m.Autocomplete("ra");
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower and upper case 
  names = m.Autocomplete("rA"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the upper case 
  names = m.Autocomplete("RA"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}

TEST(TrojanMapStudentTest, Autocomplete_2) {
  TrojanMap m;
  // Test the simple case
  auto names = m.Autocomplete("The P");
  std::unordered_set<std::string> gt = {"The Pearl", "The Peoples Independent Church of Christ"}; // groundtruth for "Ch"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower case
  names = m.Autocomplete("the p");
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the lower and upper case 
  names = m.Autocomplete("tHe p"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
  // Test the upper case 
  names = m.Autocomplete("THE P"); 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt.count(n) > 0, true) << n + " is not in gt.";
    if (gt.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt.size());
}

TEST(TrojanMapStudentTest, Autocomplete_3) {
  TrojanMap m;
  // Test the simple case
  auto names = m.Autocomplete("");
  EXPECT_EQ(0, names.size());
}



// Test FindPosition function
TEST(TrojanMapStudentTest, FindPosition) {
  TrojanMap m;
  
  // Test starbucks
  auto position = m.GetPosition("Starbucks");
  std::pair<double, double> gt1(34.0390615, -118.261117); // groundtruth for "Starbucks"
  EXPECT_EQ(position, gt1);
  // Test CAVA
  position = m.GetPosition("CAVA");
  std::pair<double, double> gt2(34.0250185, -118.2844838); // groundtruth for "CAVA"
  EXPECT_EQ(position, gt2);
  // Test Unknown
  position = m.GetPosition("");
  std::pair<double, double> gt3(-1, -1);
  EXPECT_EQ(position, gt3);
}

// Test CalculateEditDistance function
TEST(TrojanMapStudentTest, CalculateEditDistance) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("target", "tart"), 2);
  EXPECT_EQ(m.CalculateEditDistance("abcd", "cdd"), 3);
  EXPECT_EQ(m.CalculateEditDistance("abcd", "dcd"), 2);
}

// Test FindClosestName function
TEST(TrojanMapStudentTest, FindClosestName) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("cavva"), "CAVA");
  EXPECT_EQ(m.FindClosestName("dulche"), "Dulce");
  EXPECT_EQ(m.FindClosestName("pico b"), "Pico 1");
}

// Phase 2
// Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Dijkstra("Chevron", "Target");
  std::vector<std::string> gt{
      "1759017535","6653019478","6653019479","6653019482","6814990118","5617976420",
      "5617976418","1870795197","1870797819","1870797879","1870795258","1870795262",
      "1870795273","1870787390","1870795283","1870795288","1870795296","1870787411",
      "6226313826","6226313828","7867091029","7867091022","6820935938","6820972449",
      "6820972448","6820972444","6820972446","6820972447","4060015482","932416162",
      "6820935911","1837212101","1837212103","6813411589","216155217","6813411590",
      "1472141024","6813405280","348121864","348121996","6813405275","1732243544",
      "6819179749","4015372463","4015372469","1732243620","6814916523","6813379550",
      "4399697300","4399697301","4399697303","5580881629","122844997","2738332817",
      "1673644724","2738332818","1673645147","123153544","5580883117","1472141961",
      "2776870269","6814770345","5580882852","2776870272","6814770342","4536993735",
      "3431300454","6814770351","3432332948","4536989636","3433701978","6818390136",
      "6813379491","3443310465","4536989640","4536989637","6813379432","3402887075",
      "6813379464","6813379465","6813379466","6813379467","6813360936","6813360951",
      "6813379420","6813360952","6813360954","6814620882","6813360960","6813379480",
      "6813360961","6813379584","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input 
  path = m.CalculateShortestPath_Dijkstra("Target", "Chevron");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapStudentTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  
  // Test from Ralphs to Chick-fil-A
  auto path = m.CalculateShortestPath_Bellman_Ford("Chevron", "Target");
  std::vector<std::string> gt{
      "1759017535","6653019478","6653019479","6653019482","6814990118","5617976420",
      "5617976418","1870795197","1870797819","1870797879","1870795258","1870795262",
      "1870795273","1870787390","1870795283","1870795288","1870795296","1870787411",
      "6226313826","6226313828","7867091029","7867091022","6820935938","6820972449",
      "6820972448","6820972444","6820972446","6820972447","4060015482","932416162",
      "6820935911","1837212101","1837212103","6813411589","216155217","6813411590",
      "1472141024","6813405280","348121864","348121996","6813405275","1732243544",
      "6819179749","4015372463","4015372469","1732243620","6814916523","6813379550",
      "4399697300","4399697301","4399697303","5580881629","122844997","2738332817",
      "1673644724","2738332818","1673645147","123153544","5580883117","1472141961",
      "2776870269","6814770345","5580882852","2776870272","6814770342","4536993735",
      "3431300454","6814770351","3432332948","4536989636","3433701978","6818390136",
      "6813379491","3443310465","4536989640","4536989637","6813379432","3402887075",
      "6813379464","6813379465","6813379466","6813379467","6813360936","6813360951",
      "6813379420","6813360952","6813360954","6814620882","6813360960","6813379480",
      "6813360961","6813379584","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input 
  path = m.CalculateShortestPath_Bellman_Ford("Target", "Chevron");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test cycle detection function
TEST(TrojanMapStudentTest, CycleDetection) {
  TrojanMap m;
  
  // Test case 1
  std::vector<double> square1 = {-118.3, -118.275, 34.0180, 34.0165};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);

  // Test case 2 //entire graph
  std::vector<double> square2 = {-118.320, -118.250, 34.040, 34.000};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, true);

  // Test case 3 
  std::vector<double> square3 = {-118.290, -118.288, 34.020, 34.019};
  auto sub3 = m.GetSubgraph(square3);
  bool result3 = m.CycleDetection(sub3, square3);
  EXPECT_EQ(result3, false);
}



// Test topological sort function
TEST(TrojanMapStudentTest, TopologicalSort_1) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Starbucks", "Ralphs", "KFC", "CAVA"};
  std::vector<std::vector<std::string>> dependencies ={{"Starbucks","Ralphs"},{"KFC","CAVA"},{"Starbucks","KFC"},{"Ralphs","CAVA"},{"KFC","Ralphs"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Starbucks", "KFC","Ralphs","CAVA"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, TopologicalSort_2) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Starbucks", "Ralphs"};
  std::vector<std::vector<std::string>> dependencies ={{"Starbucks","Ralphs"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Starbucks", "Ralphs"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, TopologicalSort_3) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Starbucks"};
  std::vector<std::vector<std::string>> dependencies ={{"KFC","Ralphs"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Starbucks"};
  EXPECT_EQ(result, gt);
}

// Phase 3
// Test TSP function
TEST(TrojanMapStudentTest, TSP1) {
  TrojanMap m;
  
  std::vector<std::string> input{"8411386846","3398621866","6818390174","122609808","7863633188"}; // Input location ids 
  auto result = m.TravelingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"3398621866","6818390174","122609808","8411386846","7863633188","3398621866"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP2) {
  TrojanMap m;
  
  std::vector<std::string> input{"8411386846","3398621866","6818390174","122609808","7863633188"}; // Input location ids 
  auto result = m.TravelingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"8411386846","122609808","6818390174","3398621866","7863633188","8411386846"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapStudentTest, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"8411386846","3398621866","6818390174","122609808","7863633188"}; // Input location ids 
  auto result = m.TravelingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"8411386846","122609808","6818390174","3398621866","7863633188","8411386846"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (!result.second.empty() && gt == result.second.back())  // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (!result.second.empty() && gt == result.second.back())
    flag = true;
  
  EXPECT_EQ(flag, true);
}


// Test FindNearby points
TEST(TrojanMapStudentTest, FindNearby_1) {
  TrojanMap m;
  
  auto result = m.FindNearby("fuel", "target", 1, 3);
  std::vector<std::string> ans{"591042107", "9462723984"};
  EXPECT_EQ(result, ans);
}
TEST(TrojanMapStudentTest, FindNearby_2) {
  TrojanMap m;
  
  auto result = m.FindNearby("gas", "target", 1, 3);
  EXPECT_EQ(result.size(), 0);
}

TEST(TrojanMapStudentTest, FindNearby_3) {
  TrojanMap m;
  
  auto result = m.FindNearby("fuel", "target", 1, 1);
  std::vector<std::string> ans{"591042107"};
  EXPECT_EQ(result, ans);
}

// Test CalculateShortestPath_TrojanPath function
TEST(TrojanMapStudentTest, CalculateShortestPath_TrojanPath) {
  TrojanMap m;
  
  // Test for Ralphs, KFC and Chick-fil-A 
  std::vector<std::string> input = {"Target", "CAVA", "Chevron"};
  auto path = m.TrojanPath(input);
  std::vector<std::string> gt{
      "5237417650","6814769289","6813379584","6813360961","6813379480","6813360960",
      "6814620880","6814820019","6814820009","6814820016","5237417654","6814820016",
      "6814620884","6814620881","6813379467","6813379466","6813379465","6813379464",
      "3402887075","6813379432","4536989637","4536989640","3443310465","6813379491",
      "6818390136","3433701978","4536989636","3432332948","6814770351","3431300454",
      "4536993735","6814770342","2776870272","5580882852","6814770345","2776870269",
      "1472141961","5580883117","123153544","1673645147","2738332818","1673644724",
      "2738332817","122844997","5580881629","4399697303","4399697301","4399697300",
      "6813379550","6814916523","1732243620","4015372469","4015372463","6819179749",
      "1732243544","6813405275","348121996","348121864","6813405280","1472141024",
      "6813411590","216155217","6813411589","1837212103","1837212101","6820935911",
      "932416162","4060015482","6820972447","6820972446","6820972444","6820972448",
      "6820972449","6820935938","7867091022","7867091029","6226313828","6226313826",
      "1870787411","1870795296","1870795288","1870795283","1870787390","1870795273",
      "1870795262","1870795258","1870797879","1870797819","1870795197","5617976418",
      "5617976420","6814990118","6653019482","6653019479","6653019478",
      "1759017535"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  input = {"Chevron", "Target", "CAVA"};
  std::cout<<2<<std::endl;
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

  input = {"Target", "Chevron", "CAVA"};
  std::cout<<3<<std::endl;
  path = m.TrojanPath(input);
  EXPECT_EQ(path, gt);

}

// Test get all categories
TEST(TrojanMapStudentTest, GetAllCategories) {
  TrojanMap m;
  
  auto output = m.GetAllCategories();
  std::set<std::string> expected = {
    "artwork", "attraction", "bakery", "bank", "bar", "beauty", "beverages", "bicycle", "bicycle_rental",
    "bus_station", "cafe", "car", "car_repair", "car_wash", "charging_station", "childcare", "clinic",
    "clothes", "confectionery", "convenience", "copyshop", "dentist", "department_store", "driving_school",
    "fabric", "fast_food", "food_court", "fountain", "fuel", "gallery", "hairdresser", "hospital", "hotel",
    "library", "marketplace", "mobile_phone", "museum", "music", "optician", "parcel_locker", "parking",
    "parking_entrance", "pharmacy", "place_of_worship", "police", "post_box", "post_office", "restaurant",
    "school", "shoe_repair", "shoes", "skate", "social_facility", "supermarket", "theatre", "tobacco",
    "yoga", "yes"
  };
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}

TEST(TrojanMapStudentTest, GetAllLocationsFromCategory_1) {
  TrojanMap m;
  
  auto output = m.GetAllLocationsFromCategory("bakery");
  std::set<std::string> expected = {"9591449461"};
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}

TEST(TrojanMapStudentTest, GetAllLocationsFromCategory_2) {
  TrojanMap m;
  
  auto output = m.GetAllLocationsFromCategory("clothes");
  std::set<std::string> expected = {"2626144251", "5693843869", "6047198321", "6925536344", "6925536345", "9591449456"};
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}

TEST(TrojanMapStudentTest, GetAllLocationsFromCategory_3) {
  TrojanMap m;
  
  auto output = m.GetAllLocationsFromCategory("");
  std::set<std::string> expected = {};
  std::set<std::string> output_set(output.begin(), output.end());
  EXPECT_EQ(output_set, expected);
}

TEST(TrojanMapStudentTest, GetLocationRegex1) {
  TrojanMap m;
  std::set<std::string> expected_set = {"5237417650"};
  auto actual = m.GetLocationRegex(std::regex("Target"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(actual_set, expected_set);
}

TEST(TrojanMapStudentTest, GetLocationRegex2) {
  TrojanMap m;
  std::set<std::string> expected_set = { "2578244375" };
  auto actual = m.GetLocationRegex(std::regex("Rb?a.l?phs"));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}

TEST(TrojanMapStudentTest, GetLocationRegex3) {
  TrojanMap m;
  std::set<std::string> expected_set = { "4162647227", "4399693642", "5261316290" };
  auto actual = m.GetLocationRegex(std::regex("Starbucks ."));
  std::set<std::string> actual_set(actual.begin(), actual.end());
  EXPECT_EQ(expected_set, actual_set);
}


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
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
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

// // Test CalculateShortestPath_Bellman_Ford function
// TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
//   TrojanMap m;
  
//   // Test from Ralphs to Chick-fil-A
//   auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Chick-fil-A");
//   std::vector<std::string> gt{
//       "2578244375","4380040154","4380040153","4380040152","4380040148","6818427920","6818427919",
//       "6818427918","6818427892","6818427898","6818427917","6818427916","7232024780","6813416145",
//       "6813416154","6813416153","6813416152","6813416151","6813416155","6808069740","6816193785",
//       "6816193786","123152294","4015203136","4015203134","4015203133","21098539","6389467809",
//       "4015203132","3195897587","4015203129","4015203127","6352865690","6813379589","6813379483",
//       "3402887081","6814958394","3402887080","602606656","4872897515","4399697589","6814958391",
//       "123209598","6787673296","122728406","6807762271","4399697304","4399697302","5231967015",
//       "1862347583","3233702827","4540763379","6819179753","6820935900","6820935901","6813379556",
//       "6820935898","1781230450","1781230449","4015405542","4015405543","1837212104","1837212107",
//       "2753199985","6820935907","1837212100","4015372458","6813411588","1837212101","6814916516",
//       "6814916515","6820935910","4547476733"}; // Expected path
//   // Print the path lengths
//   std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//   std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//   EXPECT_EQ(path, gt);
  
//   // Reverse the input from Ralphs to Chick-fil-A
//   path = m.CalculateShortestPath_Bellman_Ford("Chick-fil-A", "Ralphs");
//   std::reverse(gt.begin(),gt.end()); // Reverse the path

//   // Print the path lengths
//   std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//   std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//   EXPECT_EQ(path, gt);
// }

// // Test cycle detection function
// TEST(TrojanMapTest, CycleDetection) {
//   TrojanMap m;
  
//   // Test case 1
//   std::vector<double> square1 = {-118.299, -118.264, 34.032, 34.011};
//   auto sub1 = m.GetSubgraph(square1);
//   bool result1 = m.CycleDetection(sub1, square1);
//   EXPECT_EQ(result1, true);

//   // Test case 2
//   std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
//   auto sub2 = m.GetSubgraph(square2);
//   bool result2 = m.CycleDetection(sub2, square2);
//   EXPECT_EQ(result2, false);
// }



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

// // Phase 3
// // Test TSP function
// TEST(TrojanMapTest, TSP1) {
//   TrojanMap m;
  
//   std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
//   auto result = m.TravelingTrojan_Brute_force(input);
//   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
//   std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
//   std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
//   bool flag = false;
//   if (!result.second.empty() && gt == result.second.back())  // clockwise
//     flag = true;
//   std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
//   if (!result.second.empty() && gt == result.second.back())
//     flag = true;
  
//   EXPECT_EQ(flag, true);
// }

// TEST(TrojanMapTest, TSP2) {
//   TrojanMap m;
  
//   std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
//   auto result = m.TravelingTrojan_Backtracking(input);
//   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
//   std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
//   std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
//   bool flag = false;
//   if (!result.second.empty() && gt == result.second.back()) // clockwise
//     flag = true;
//   std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
//   if (!result.second.empty() && gt == result.second.back())
//     flag = true;
  
//   EXPECT_EQ(flag, true);
// }

// TEST(TrojanMapTest, TSP3) {
//   TrojanMap m;
  
//   std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
//   auto result = m.TravelingTrojan_2opt(input);
//   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
//   std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
//   std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
//   bool flag = false;
//   if (!result.second.empty() && gt == result.second.back()) // clockwise
//     flag = true;
//   std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
//   if (!result.second.empty() && gt == result.second.back())
//     flag = true;
  
//   EXPECT_EQ(flag, true);
// }

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

TEST(TrojanMapStudentTest, FindNearby_1) {
  TrojanMap m;
  
  auto result = m.FindNearby("fuel", "target", 1, 1);
  std::vector<std::string> ans{"591042107"};
  EXPECT_EQ(result, ans);
}

// // Test CalculateShortestPath_TrojanPath function
// TEST(TrojanMapTest, CalculateShortestPath_TrojanPath) {
//   TrojanMap m;
  
//   // Test for Ralphs, KFC and Chick-fil-A 
//   std::vector<std::string> input = {"KFC", "Ralphs", "Chick-fil-A"};
//   auto path = m.TrojanPath(input);
//   std::vector<std::string> gt{
//       "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131",
//       "7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705",
//       "6816193774","452688933","452688931","123230412","6816193770","6787470576","4015442011",
//       "6816193692","6816193693","6816193694","3398621886","3398621887","6816193695","5690152756",
//       "6804883324","3398621888","6813416123","6813416171","6807536647","6807320427","6807536642",
//       "6813416166","7882624618","7200139036","122814440","6813416163","7477947679","7298150111",
//       "6787803640","6807554573","2613117890","4835551096","4835551101","4835551097","4835551100",
//       "3088547686","4835551100","4835551099","4835551098","6813565307","6813565306","6813565305",
//       "6813565295","6813565296","3402814832","4835551107","6813379403","6813379533","3402814831",
//       "6813379501","3402810298","6813565327","3398574883","6813379494","6813379495","6813379544",
//       "6813379545","6813379536","6813379546","6813379547","6814916522","6814916523","1732243620",
//       "4015372469","4015372463","6819179749","1732243544","6813405275","348121996","348121864",
//       "6813405280","1472141024","6813411590","216155217","6813411589","1837212103","1837212101",
//       "6814916516","6814916515","6820935910","4547476733"}; // Expected path
//   // Print the path lengths
//   std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
//   std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
//   EXPECT_EQ(path, gt);

//   input = {"Ralphs", "Chick-fil-A", "KFC"};
//   path = m.TrojanPath(input);
//   EXPECT_EQ(path, gt);

//   input = {"Ralphs", "KFC", "Chick-fil-A"};
//   path = m.TrojanPath(input);
//   EXPECT_EQ(path, gt);

// }

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


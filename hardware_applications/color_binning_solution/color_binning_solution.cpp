#include <iostream>
#include <algorithm>
#include <vector>

#include <STSL/RJRobot.h>

using namespace std;

const int black_thresh = 2000;

int main() {
  RJRobot robot(RobotType::REAL);

  robot.SetDriveMotors(100, 100);

  vector<int> values;
  int value;
  do {
    value = robot.GetLineValue(LineSensor::CENTER);
    values.push_back(value);
  } while (value < black_thresh);

  robot.StopMotors();

  transform(values.begin(), values.end(), values.begin(), [](int v) {
    return v / 256;
  });

  for (int i = 0; i < 16; i++) {
    cout << "bin " << i << " has " << count(values.begin(), values.end(), i) << " readings" << endl;
  }

  vector<int> bin_counts;
  for_each(values.begin(), values.end(), [&bin_counts](int x) {
    bin_counts[x / 256] += 1;
  });

  for (int i = 0; i < bin_counts.size(); i++) {
    cout << "bin " << i << " has " << bin_counts[i] << " readings" << endl;
  }
}

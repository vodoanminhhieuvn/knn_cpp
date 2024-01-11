#include <fmt/core.h>
#include <iostream>
#include <lib/k_nearest_neighbors.h>
#include <lib/utils.h>
#include <matplot/matplot.h>

LabelPoint parse_iris_row(const std::vector<std::string> &row) {
  std::vector<double> measurements;
  for (size_t i = 0; i < row.size() - 1; ++i) {
    measurements.push_back(std::stod(row[i]));
  }

  std::string label = row.back().substr(row.back().find_last_of("-") + 1);

  return LabelPoint{measurements, label};
}

void testing_knn() {
  // Extract data
  std::ifstream file("./iris.data");
  std::string line;

  std::vector<LabelPoint> iris_data;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::vector<std::string> row;

      while (iss) {
        std::string value;
        if (!std::getline(iss, value, ',')) {
          break;
        }
        row.push_back(value);
      }

      if (!row.empty()) {
        iris_data.push_back(parse_iris_row(row));
      }
    }

    file.close();
  } else {
    std::cerr << "Unable to open file\n";
  }

  // Visualize our data

  /* std::map<std::string, std::vector<Vector>> points_by_species; */
  /* for (const auto &iris : iris_data) { */
  /*   points_by_species[iris.label].push_back(iris.point); */
  /* } */
  /**/
  /* std::vector<std::string> metrics = {"sepal length", "sepal width", */
  /*                                     "petal length", "petal width"}; */
  /* std::vector<std::pair<int, int>> pairs; */
  /* std::vector<std::string> marks = {"+", ".", "x"}; */
  /**/
  /* for (int i = 0; i < 4; ++i) { */
  /*   for (int j = i + 1; j < 4; ++j) { */
  /*     pairs.push_back(std::make_pair(i, j)); */
  /*   } */
  /* } */
  /**/
  /* matplot::tiledlayout(2, 3); */
  /* for (size_t p = 0; p < pairs.size(); ++p) { */
  /*   int i = pairs[p].first; */
  /*   int j = pairs[p].second; */
  /*   auto sp = matplot::nexttile(); */
  /*   sp->title(fmt::format("{} vs {}", metrics[i], metrics[j])); */
  /*   for (size_t m = 0; m < marks.size(); ++m) { */
  /*     const auto &[species, points] = *std::next(points_by_species.begin(), m); */
  /*     Vector xs, ys; */
  /*     for (const auto &point : points) { */
  /*       xs.push_back(point[i]); */
  /*       ys.push_back(point[j]); */
  /*     } */
  /*     matplot::scatter(xs, ys)->marker(marks[m]).display_name(species); */
  /*     matplot::hold(true); */
  /*   } */
  /* } */
  /* matplot::legend("lower right") */
  /*     ->location(matplot::legend::general_alignment::bottomright); */
  /* matplot::legend()->font_size(6); */
  /* matplot::show(); */

  // Split and predict
  std::srand(12);

  auto split_result = split_data(iris_data, 0.70);

  const std::vector<LabelPoint> &iris_train = split_result.first;
  const std::vector<LabelPoint> &iris_test = split_result.second;

  assert(iris_train.size() == static_cast<size_t>(0.7 * iris_data.size()));
  assert(iris_test.size() == static_cast<size_t>(0.3 * iris_data.size()));

  std::unordered_map<std::tuple<std::string, std::string>, int, TupleHash>
      confusion_matrix;
  int num_correct = 0;

  for (const auto &iris : iris_test) {
    std::string predicted = knn::knn_classify(5, iris_train, iris.point);
    std::string actual = iris.label;

    if (predicted == actual) {
      num_correct++;
    }

    confusion_matrix[{predicted, actual}]++;
  }

  // Visualize confusion_matrix

  double pct_correct = static_cast<double>(num_correct) / iris_test.size();
  std::cout << pct_correct << std::endl;

  std::vector<std::string> labels = {"setosa", "versicolor", "virginica"};
  std::vector<std::vector<double>> counts(
      labels.size(), std::vector<double>(labels.size(), 0));

  for (const auto &entry : confusion_matrix) {
    const auto &key = entry.first;
    size_t predicted_index =
        std::find(labels.begin(), labels.end(), std::get<0>(key)) -
        labels.begin();
    size_t actual_index =
        std::find(labels.begin(), labels.end(), std::get<1>(key)) -
        labels.begin();
    counts[predicted_index][actual_index] = static_cast<double>(entry.second);
  }

  matplot::gca()->children({});

  matplot::heatmap(counts);
  matplot::title("Confusion Matrix Heatmap");
  auto ax = matplot::gca();
  ax->x_axis().ticklabels(labels);
  ax->y_axis().ticklabels(labels);
  matplot::xlabel(ax, "Actual Labels");
  matplot::ylabel(ax, "Predicted Labels");
  matplot::show();
}

int main() { testing_knn(); }

/*
 * CS106L Assignment 4: Weather Forecast
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 */

#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

/* #### Please feel free to use these values, but don't change them! #### */
double kMaxTempRequirement = 5;
double uAvgTempRequirement = 60;

struct Forecast
{
  double min_temp;
  double max_temp;
  double avg_temp;
};

Forecast compute_forecast(const std::vector<double> &dailyWeather)
{
  // STUDENT TODO 1: return a forecast for the daily weather that is passed in.
  // 学生任务 1：根据传入的每日天气，返回一个天气预报。
  Forecast forecast;
  // 这两个函数返回的都是迭代器，如果要值，需要加上*
  forecast.min_temp = *std::min_element(dailyWeather.begin(), dailyWeather.end());
  forecast.max_temp = *std::max_element(dailyWeather.begin(), dailyWeather.end());
  //注意数据类型，防止溢出
  forecast.avg_temp = std::accumulate(dailyWeather.begin(), dailyWeather.end(), (double)0.00) / (double)dailyWeather.size();
  return forecast;
}

std::vector<Forecast> get_forecasts(const std::vector<std::vector<double>> &weatherData)
{
  /*
   * STUDENT TODO 2: returns a vector of Forecast structs for the weatherData which contains
   * 学生任务 2：返回一个包含 Forecast 结构体的向量，该向量对应 weatherData。
   * std::vector<double> which contain values for the weather on that day.
   * 其中，weatherData 包含一个 std::vector<double>，表示当天的天气数据。
   */
  std::vector<Forecast> forecast;

  // 根据README文件更换transform修改的
  std::transform(weatherData.begin(), weatherData.end(), std::back_inserter(forecast), [](const std::vector<double> &deal)
                 { return compute_forecast(deal); });

  // 打a老习惯写的
  //  for (const auto &i : weatherData)
  //    forecast.push_back(compute_forecast(i));
  return forecast;
}

std::vector<Forecast> get_filtered_data(const std::vector<Forecast> &forecastData)
{
  // STUDENT TODO 3: 返回筛选后的包含特定天气数据的 Forecast 向量
  // STUDENT TODO 3: return a vector with Forecasts filtered for days with specific weather.

  // 干！他不让我用copy_if
  //  std::vector<Forecast> filtered_data;
  //   std::copy_if(forecastData.begin(), forecastData.end(), std::back_inserter(filtered_data), [](const Forecast daydata)
  //                { return (daydata.max_temp - daydata.min_temp) > kMaxTempRequirement && daydata.avg_temp >= uAvgTempRequirement; });
  //   return filtered_data;

  std::vector<Forecast> filtered_data(forecastData.begin(), forecastData.end());

  auto new_end = std::remove_if(filtered_data.begin(), filtered_data.end(), [](const Forecast &daydata)
                                { return ((daydata.max_temp - daydata.min_temp) <= kMaxTempRequirement || daydata.avg_temp < uAvgTempRequirement); });
  filtered_data.erase(new_end, filtered_data.end());

  return filtered_data;
}

std::vector<Forecast> get_shuffled_data(const std::vector<Forecast> &forecastData)
{
  // STUDENT TODO 4: Make use of a standard library algorithm to shuffle the data!
  // STUDENT TODO 4: 使用标准库算法来打乱数据！
  // 随机种子
  std::random_device rd;
  std::mt19937 g(rd());

  std::vector<Forecast> shuffle_data(forecastData.begin(), forecastData.end());
  // 打乱
  std::shuffle(shuffle_data.begin(), shuffle_data.end(), g);

  return shuffle_data;
}

std::vector<Forecast> run_weather_pipeline(const std::vector<std::vector<double>> &weatherData)
{
  // STUDENT TODO 5: Put your functions together to run the weather pipeline!
  // STUDENT TODO 5: 将你的函数组合在一起，运行天气数据处理流程！
  std::vector<Forecast> forecasts = get_forecasts(weatherData);
  std::vector<Forecast> filteredData = get_filtered_data(forecasts);
  std::vector<Forecast> shuffledData = get_shuffled_data(filteredData);
  return shuffledData;
}

/* #### Please don't change this line! #### */
#include "utils.cpp"
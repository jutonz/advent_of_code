defmodule Day1 do
  def part1 do
    {col1_values, col2_values} = extract_values()

    col1_values = Enum.sort(col1_values)
    col2_values = Enum.sort(col2_values)

    result =
      Enum.reduce(Enum.with_index(col1_values), 0, fn {col1_value, index}, acc ->
        acc + abs(col1_value - Enum.at(col2_values, index))
      end)
  end

  def part2 do
    {col1_values, col2_values} = extract_values()

    col1_values
    |> Enum.reduce(%{}, &map_occurrence_count(col2_values, &1, &2))
    |> Map.to_list()
    |> Enum.map(fn {k, v} -> k * v end)
    |> Enum.sum()
    |> IO.puts()
  end

  defp map_occurrence_count(list, value, map) do
    Map.put(map, value, count_occurrences(list, value))
  end

  defp count_occurrences(list, target) do
    Enum.reduce(list, 0, fn value, acc ->
      if value == target do
        acc + 1
      else
        acc
      end
    end)
  end

  defp extract_values do
    "./input.txt"
    |> File.read!()
    |> String.split("\n")
    |> Enum.reject(fn line -> line == "" end)
    |> Enum.map(&String.split(&1, "   "))
    |> Enum.reduce({[], []}, fn [col1_value, col2_value], {col1_values, col2_values} ->
      {
        [String.to_integer(col1_value) | col1_values],
        [String.to_integer(col2_value) | col2_values]
      }
    end)
  end
end

Day1.part2()

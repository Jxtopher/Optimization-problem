# https://www.csplib.org/Problems/prob054/
# Execute the code: elixir nqueens.exs

defmodule Nqueens do
  defmodule Constraint do
    def diago?(solution, a), do: diago?(solution, a, 1)

    def diago?([], _, _), do: true

    def diago?([head | tail], a, depth)
        when abs(head - a) != depth,
        do: diago?(tail, a, depth + 1)

    def diago?(_, _, _), do: false

    def line?([], _), do: true
    def line?([head | tail], a) when head != a, do: line?(tail, a)
    def line?(_, _), do: false

    def constrains?(solution, a) do
      line?(solution, a) and diago?(solution, a)
    end
  end

  def solve(n), do: solve(n, [], 0)
  def solve(n, solution, depth) when depth == n, do: solution

  def solve(n, solution, depth) do
    Enum.reduce(0..(n - 1), [], fn i, acc ->
      if Constraint.constrains?(solution, i) do
        if depth + 1 == n do
          acc ++ [solve(n, [i] ++ solution, depth + 1)]
        else
          acc ++ solve(n, [i] ++ solution, depth + 1)
        end
      else
        acc
      end
    end)
  end

  # main
  def main([]) do
    IO.puts("Usage: elixir n-queens.exs n, with n >= 4")

    IO.puts("Default parmater N = 4")
    main(["4"])
  end

  def main(args) do
    [arg] = args

    IO.puts("NQueens solver, N = " <> arg)

    n = String.to_integer(arg)

    solutions = solve(n)

    IO.puts("Number of solutions found #{length(solutions)}")

    IO.puts("Example of solution found:")
    solution = Enum.at(solutions, 0)
    IO.inspect(solution)

    for i <- 0..n do
      for j <- 0..n do
        if Enum.at(solution, i) == j do
          IO.write("⬛")
        else
          IO.write("⬜")
        end
      end

      IO.puts("")
    end
  end
end

# Run the main function with command-line arguments
Nqueens.main(System.argv())

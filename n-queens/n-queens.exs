# elixir n-queens.exs n

defmodule Stack do
  use GenServer

  @impl true
  def init(stack), do: {:ok, stack}

  @impl true
  def handle_call(:pop, _from, [head | tail]), do: {:reply, head, tail}

  @impl true
  def handle_call(:size, _from, state), do: {:reply, length(state), state}

  @impl true
  def handle_cast({:push, element}, state), do: {:noreply, [element | state]}
end

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

    def constrains?(solution, a), do: line?(solution, a) and diago?(solution, a)
  end

  defmodule Solve do
    def exploration(n, [], depth, results_acc), do: breadth(n, [0], depth, results_acc)

    def exploration(n, [head | tail], depth, results_acc) do
      if Constraint.constrains?(tail, head) do
        breadth(n, [0] ++ [head | tail], depth, results_acc)
      end
    end

    def breadth(n, solution, depth, results_acc) do
      if length(solution) == n + 1 do
        [head | tail] = solution

        if Constraint.constrains?(tail, head) do
          # IO.inspect([solution, depth])
          GenServer.cast(results_acc, {:push, solution})
        end
      end

      if depth < n do
        exploration(n, solution, depth + 1, results_acc)
      end

      [head | tail] = solution

      if head < n do
        breadth(n, [head + 1 | tail], depth, results_acc)
      end
    end
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

    n = String.to_integer(arg) - 1

    {:ok, results_acc} = GenServer.start_link(Stack, [])

    Solve.exploration(n, [], 0, results_acc)

    IO.puts("Number of solutions found #{GenServer.call(results_acc, :size)}")

    IO.puts("Example of solution found:")
    solution = GenServer.call(results_acc, :pop)
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

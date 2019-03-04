%% swipl n-queens.pl


domaine(X, L) :- member(X, L).

% Construction de la liste L entre MIN et MAX
build_list(MAX, MAX, L) :- L = [], !.
build_list(MIN, MAX, L) :-
  MIN < MAX,
  NEW_MIN is MIN + 1,
  build_list(NEW_MIN, MAX, NEW_L),
  append([MIN], NEW_L, L).

% Vérification des lignes
checkLine([]):- !.
checkLine([X|SOLUTION]):-
  not(member(X, SOLUTION)),
  checkLine(SOLUTION).

% Vérification des diagonales
checkDiagonal([_]):- !.
checkDiagonal([X|SOLUTION]):-
  sous([X|SOLUTION], 0),
  checkDiagonal(SOLUTION).

sous([_], _):- !.
sous([X, Y|SOLUTION], D):-
  NEW_D is D + 1,

  TEMP is abs(X - Y),
  TEMP \= NEW_D,

  NEW_D is D + 1,
  sous([X|SOLUTION], NEW_D).


nreine(N, K, SOLUTION) :-
  K =< 0,
  SOLUTION = [],
  !.

nreine(N, K, SOLUTION) :-
  0 < K,

  % Construction du domaine pour ieme
  %length(SOLUTION, SIZE),
  build_list(0, N, L),
  domaine(DOMAIN, L),

  NEW_K is K - 1,
  nreine(N, NEW_K, NEW_SOLUTION),
  append([DOMAIN], NEW_SOLUTION, SOLUTION),
  checkLine(SOLUTION),
  checkDiagonal(SOLUTION).
  %writeln(SOLUTION).


solver(N):-
    nreine(N, N, SOLUTION),
    writeln(SOLUTION).

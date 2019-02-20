noun(["dog"]).
noun(["man"]).
noun(["banana"]).


article(["a"]).
article(["an"]).
article(["the"]).

verb(["ate"]).
verb(["walks"]).

%sentence(L-[]) :- nounphrase(L-S1), verbphrase(S1-[]).
%nounphrase(L-S1) :- noun(L).
%nounphrase(L-S1) :- article(L), nounphrase(S1).

read_words(W) :- read_string(user_input, "\n\r", "\n\r", _, L),split_string(L,"\t ", "\t ", W).

% C =..[noun,dog].
% C = noun(dog).

%                   Basics of Game Loop
% play() :-
% here(H),
% look(H),
% read_words(W),
% parse(W, C),          C stands for command
% C,                    execute the command
% won,                  check if the user has won

% reset_game() :- blah

% C =.. AtomList        is key to parse function


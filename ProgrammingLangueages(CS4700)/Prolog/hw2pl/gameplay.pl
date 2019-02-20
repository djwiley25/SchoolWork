:-include(adventure).

%Symmetric
is_connected(X,Y) :-door(X,Y).
is_connected(X,Y) :-door(Y,X).

show_connections(X) :- is_connected(X,Y), name(Y,N), write(N), write('\n'), fail.
show_connections(_).

list_items(L) :- location(X,L), name(X,N), write(N), write(" -"), write_short_desc(X,SD),write('\n'),fail.
list_items(_).

list_items_long(X) :- name(X,N), write(N), write(" -"), write_long_desc(X,LD), write('\n'), fail.
list_items_long(_).

write_short_desc(X) :- short_desc(X,SD), write(SD),write('\n'),!.
write_long_desc(X) :- long_desc(X,LD), write(LD), write('\n'),!.

%Unchecked look
look(L) :- room(L), write(L), write(" :"), write('\n'), write_long_desc(L), write('\n'),
write("Items Contained:"), write('\n'), list_items(L), write('\n'), write("Areas Connected:"), write('\n'), show_connections(L), write('\n'),!.
look(C) :- container(C), write(C), write(" :"), write('\n'), write_short_desc(C), write('\n'), write("There may be something inside this container!!"),!.
look(X) :- write(X), write(" :"), write('\n'), write_short_desc(X),!.

%Look with no arguments is just look at current location, became annoying trying to test and remember current location name
look :- here(L), look(L).

%Checked look
is_in_location(X,L) :- location(X,L),is_in_location(C, L).
is_in_location(X,L) :- X == L,!.

checked_look(X) :- here(L), is_in_location(X,L), look(X),!.
checked_look(L) :- here(L), look(L),!.
checked_look(I) :- has(I), look(I),!.
checked_look(C) :- container(C), location(C,L), here(L), look(C),!.


%Unchecked study
study(L) :- room(L), look(L),!.
study(C) :- container(C), write(C), write(" :"), write('\n'), write_long_desc(C), write('\n'), list_items(C),!.
study(X) :- write(X), write(" :"), write('\n'), write_long_desc(X),!.

%Checked study
checked_study(X) :- here(Y), is_in_location(X, Y), study(X),!.
checked_study(X) :- has(X), study(X),!.

%Unchecked inventory
display_inventory(X) :- has(X),write(X),write(" -"),write_short_desc(X), write('\n'), fail.
display_inventory(_).

inventory :- display_inventory(_),!.

%Checked inventory





%Unchecked move
move(L) :- retract(here(_)),assert(here(X)),!.

%Checked move
checked_move(X) :- assert(has(X)),retract(location(X,_)).

%Unchecked take
take(X) :- not(heavy(X)), assert(has(X)), retract(location(X,_)), !, write('\n'), write("You have taken: "), write(X), write("."),!.

%Checked take
checked_take(X) :- not(heavy(X)),here(Y),is_in_location(X,Y),take(X),!.
checked_take(X,C) :- location(X,C),here(Y),is_in_location(C,Y),take(X),!.
checked_take(X,C) :- has(C),take(X).


%Unchecked make and the needed functions

check_ingredients([]),
check ingredients([H|T]) :- has(H), check_ingredients(T).

use_ingredients([]) :- !.
use_ingredients([H|T]) :- retract(has(H)), use_ingredients(T).

make(X) :- create_recipe(E,I,X), here(Y), is_in_location(E,Y), check_ingredients(I), use_ingredients(I), assert(has(X)),!.

%Checked make






%Unchecked put
put(X) :- has(X), retract(has(X)), here(L), assert(location(X,L)).
put(X,L) :- retract(has(X)), assert(location(X,L)).

%Checked put
checked_put(X,L) :- here(L),place(X,L),!.
checked_put(X,C) :- container(C),has(C),put(X,C),!.
checked_put(X,C) :- container(C),here(Y),is_in_location(C,Y),put(X,C),!.

%transfer and Towers of Hanoi
win :- location(large_disk,pylon_c), location(medium_disk,pylon_c), location(small_disk,pylon_c), here(secret_lab), write("You won!").

transfer(small_disk,P) :- retract(location(small_disk,_)), assert(location(small_disk,P)).
transfer(medium_disk,P) :- not(location(small_disk,P)), location(medium_disk,L), not(location(small_disk,L)), retract(location(medium_disk,_)), assert(location(medium_disk,P)).
transfer(large_disk,P) :- not(location(small_disk,P)), not(location(medium_disk,P)), location(large_disk,L), not(location(small_disk,L)), retract(location(large_disk,_)), assert(location(large_disk,P)).

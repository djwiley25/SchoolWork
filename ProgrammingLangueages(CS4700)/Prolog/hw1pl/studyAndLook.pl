:-include(adventure).

is_connected(X,Y) :-door(X,Y).
is_connected(X,Y) :-door(Y,X).

show_connections(X) :- is_connected(X,Y), name(Y,N), write(N), write('\n'), fail.
show_connections(_).

list_items(L):-location(X,L),name(X,N),short_desc(X,SD),format('~w: ~w', [N,SD]),write('\n'),fail.
list_items(_).

list_items_long(X):- name(X,N), long_desc(X,LD), format('~w(~w) ~NContents: ~w~N', [N,X,LD]), write('\n'), fail.
list_items_long(_).

write_short_desc(X):-short_desc(X,SD), write(SD),write('\n').

look(X) :- name(X,N), write(N), write('\n'), write("Items Contained:"), write('\n'), list_items(X), write('\n'), write("Areas Connected:"), write('\n'), show_connections(X), write('\n'), write("Area Description:"), write('\n'), write_short_desc(X), write('\n'),!.

study(X) :- show_connectionsLong(X), write('\n').

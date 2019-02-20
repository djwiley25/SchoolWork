city(logan).
city(slc).
city(st_george).
city(las_vegas).
city(los_angeles).
city(denver).
city(chicago).
city(tacoma).
city(san_franciso).
city(new_york).

connection(logan, slc).
connection(slc, denver).
connection(slc, st_george).
connection(las_vegas, los_angeles).
connection(las_vegas, denver).
connection(las_vegas, slc).
connection(las_vegas, san_franciso).
connection(los_angeles, san_franciso).
connection(denver,san_franciso).
connection(denver, new_york).
connection(slc, tacoma).

is_connected(X,Y) :- connection(X,Y).
is_connected(X,Y) :- connection(Y,X).

route(X,Y) :- is_connected(X,Y).
route(X,Y) :- is_connected(X,Z),route(Z,Y).

visited(X,[X | _]).
visited(X,[_ | T]) :- visited(X,T).
visited(_,[]) :- fail.

not_visited(X,P) :- visited(X,P), !, fail.
not_visited(_,_).

path(X,Y,_,[X,Y]) :- is_connected(X,Y).
path(X,Y,SoFar,[X | P]) :- is_connected(X,Z),not_visited(Z,SoFar),path(Z,Y,[Z | SoFar],P).

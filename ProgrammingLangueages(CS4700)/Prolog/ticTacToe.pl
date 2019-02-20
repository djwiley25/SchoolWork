:- dynamic cell/3.
:- dynamic turn/1.

turn(x).

nextturn(x,o).
nextturn(o,x).

win(Player) :- cell(Row,a,Player),cell(Row,b,Player),cell(Row,c,Player).
win(Player) :- cell(a,Col,Player),cell(b,Col,Player),cell(c,Col,Player).
win(Player) :- cell(a,a,Player),cell(b,b,Player),cell(c,c,Player).
win(Player) :- cell(a,c,Player),cell(b,b,Player),cell(c,a,Player).

done :- win(_).
done :- cell(a,a,_),cell(a,b,_),cell(a,c,_),
        cell(b,a,_),cell(b,b,_),cell(b,c,_),
        cell(c,a,_),cell(c,b,_),cell(c,c,_).

writecell(R,C) :- cell(R,C,x),!,write('X').
writecell(R,C) :- cell(R,C,o),!,write('O').
writecell(_,_) :- write('  ').

showplayer :-win(x),!,write('X has won!\n').
showplayer :-win(x),!,write('O has won!\n').
showplayer :-turn(x),!,write('It is X\'s turn. \n').
showplayer :-turn(o),!,write('It is O\'s turn. \n').



show :- writecell(a,a),write('|'),writecell(a,b),write('|'),writecell(a,c),
        write('\n----\n'),
        writecell(b,a),write('|'),writecell(b,b),write('|'),writecell(b,c),
        write('\n----\n'),
        writecell(c,a),write('|'),writecell(c,b),write('|'),writecell(c,c),
        write('\n'),showplayer.


canmove(Row,Col):-cell(Row,Col,_),!,fail.
canmove(_,_):-done,!,fail.
canmove(_,_).

move(Row,Col) :-  canmove(Row,Col),turn(Player),
                  assertz(cell(Row,Col,Player)),
                  retract(turn(Player)),
                  nextturn(Player,NewPlayer),
                  assertz(turn(NewPlayer)),!,show.

clear:-turn(Cur),retract(turn(Cur)),assertz(turn(x)),cell(R,C,P),retract(cell(R,C,P)),fail.

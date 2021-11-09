%        KNOWLEDGE BASE 

team(realmadrid, madrid).
team(juventus, torino).
team(galatasaray, istanbul).
team(kobenhavn, copenhagen).
team(manutd, manchester).
team(realsociedad, sansebastian).
team(shaktard, donetsk).
team(bleverkusen, leverkusen).
team(omarseille, marseille).
team(arsenal, london).
team(fcnapoli, napoli).
team(bdortmund, dortmund).


%---------------QUESTION 0.1--------------
%In the first question I use findall function to find all teams each other
%After that i send all teams to TE array to keep the length of that array i used length function 
%After that i used Permutation function

allteams(L,N):-
    
  findall(A,team(A,_),TE),
    
  length(TE,N),
    
  permutation(TE,L).


match(1, galatasaray, 1, realmadrid, 6).
match(1, kobenhavn, 1, juventus, 1).
match(1, manutd, 4, leverkusen, 2).
match(1, realsociedad, 0, shaktard, 2).
match(1, omarseille, 1, arsenal, 2).
match(1, fcnapoli, 2, bdortmund, 1).

match(2, juventus, 2, galatasaray, 2).
match(2, realmadrid, 4, kobenhavn, 0).
match(2, shaktard, 2, manutd, 3).
match(2, bleverkusen, 1, realsociedad, 1).
match(2, bdortmund, 3, omarseille, 0).
match(2, arsenal, 2, fcnapoli, 0).

match(3, galatasaray, 3, kobenhavn, 1).
match(3, realmadrid, 2, juventus, 1).
match(3, manutd, 1, realsociedad, 0).
match(3, bleverkusen, 4, shaktard, 0).
match(3, omarseille, 1, fcnapoli, 2).
match(3, arsenal, 1, bdortmund, 2).

match(4, kobenhavn, 1, galatasaray, 0).
match(4, juventus, 2, realmadrid, 2).
match(4, bleverkusen, 0, manutd, 5).
match(4, shaktard, 4, realsociedad, 0).
match(4, fcnapoli, 4, omarseille, 2).
match(4, bdortmund, 0, arsenal, 1).

match(5, realmadrid, 4, galatasaray, 1).
match(5, juventus, 3, kobenhavn, 1).
match(5, realsociedad, 0, manutd, 0).
match(5, shaktard, 0, bleverkusen, 0).
match(5, bdortmund, 3, fcnapoli, 1).
match(5, arsenal, 2, omarseille, 0).

match(6, galatasaray, 1, juventus, 0).
match(6, kobenhavn, 0, realmadrid, 2).
match(6, manutd, 1, shaktard, 0).
match(6, realsociedad, 2, bleverkusen, 0).
match(6, omarseille, 1, bdortmund, 2).
match(6, fcnapoli, 2, arsenal, 0).

%----------------------QUESTION 0.2---------------------

%I found two different situation if a team scored more than got scored home and away matches 
%the team will be winner i kept two different information in different arrays and append them 
%each other 
%in other cases i followed that ways and looked the situaiton that if a team got scored more 
%than scored it is a looser team and in the last case if the scored and being got scored 
%situations are same these teams are in draw situation

wins(T,W,L,N):-
	
  findall(LT,(match(X,T,SC,LT,GS),X=<W,SC>GS),L1),
    
  findall(LT,(match(X,LT,GS,T,SC),X=<W,SC>GS),L2),
    
  append(L1,L2,L),
    
  length(L,N).



loses(T,W,L,N):-
	
  findall(LT,(match(X,T,SC,LT,GS),X=<W,SC<GS),L1),
    
  findall(LT,(match(X,LT,GS,T,SC),X=<W,SC<GS),L2),
    
  append(L1,L2,L),
    
  length(L,N).



draws(T,W,L,N):-
	
  findall(LT,(match(X,T,SC,LT,GS),X=<W,SC=GS),L1),
    
  findall(LT,(match(X,LT,GS,T,SC),X=<W,SC=GS),L2),
    
  append(L1,L2,L),
    
  length(L,N).


%----------------------QUESTION 0.3-----------------------------------

%In the first part i found the team's scores until selected week these scored contains 
%the all goals which have been scored in home and away matches to keep that information i looked
%that in two different arrays and append that information to single array 
%and used sumlist method to sumall numbers of that array and assing this summation to the S value  
%for other cases i used that way and evaluate conceded situation
%in average part I calculated the GS(getting scored) and SC(scored) numbers for a team 
%and substitued these values to find that team's average in S value


scored(T,W,S):-
    
  findall(SC,(match(X,T,SC,_,_),X=<W),AV1),
    
  findall(SC,(match(X,_,_,T,SC),X=<W),AV2),
    
  append(AV1,AV2,L),
	
  sumlist(L,S).



conceded(T,W,S):-
    
  findall(GS,(match(X,T,_,_,GS),X=<W),AV1),
    
  findall(GS,(match(X,_,_,GS,T),X=<W),AV2),
    
  append(AV1,AV2,L),
	
  sumlist(L,S).


average(T,W,S):-
   	
  findall(SC,(match(X,T,SC,_,_),X=<W),AV1),
    
  findall(SC,(match(X,_,_,T,SC),X=<W),AV2),
    
  append(AV1,AV2,L1),
    
  sumlist(L1,S1),
    
  findall(GS,(match(X,T,_,_,GS),X=<W),AV3),
    
  findall(GS,(match(X,_,_,GS,T),X=<W),AV4),
    
  append(AV3,AV4,L2),
    
  sumlist(L2,S2),
	
  S is S1-S2.

%---------------------QUESTION 0.4--------------------
%I found the names off all teams and also found averages of all names 
%After that I sorted the teams according to their averages  

order(L,W):-
    
  findall(X,team(X,_),LI),
    
  teamavg(LI,W,L1),
    
  sort(2, @>=, L1, L2),
	
  tnames(L2,L3),
	
  reverse(L3,L).



teamavg([],W,L1).

teamavg([X|T],W,L1):-
    
  average(X,W,S),
    
  teamavg(T,W,L2),
    
  append(L2,[[X,S]],L1).

tnames([H|T],L3):-
    
  select(H,H1),
	
  tnames(T,L4),
	
  append(L4,[H1],L3).


tnames([],L3).
	

topThree([X,Y,Z],W):-
    
  order(L,W),
    
  [X,Y,Z|_]=L.


select([X|_],X).








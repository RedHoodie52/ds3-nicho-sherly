Namen: Sherly Sutrisno, s3660621 & Nicholas Wu, s3692949

Met behulp van de sudo code hebben we reguliere expressies omgezet in eindige autmaten.
Hierbij hebben we 3 functies geimplementeerd: "Concat", "Star" en "Union".


Niks aan toe te voegen alles werkt perfect!



Welke representatie is er gekozen 
waarom is die representatie gekozen
voorbeeld expressie:
resulterende automaat:

Om de automaat te representeren hebben we gebruik gemaakt van een std::vector<std::vector<int>>;
Hiermee kunnen we de transitties in een tabel doen waar je makkelijk bij kunt komen met vector operaties. 
De 4 kolommen zijn respectievelijk voor de "from-state", "symbol", "to-state-1" en "to-state-2".

Nu een voorbeeld:
We nemen de reguliere expressie ((ab)*c)|d
Dan krijgen we de volgende automaat:

From State      Symbol  To State 1      To State 2
1               a               2               0
2               $               3               0
3               b               4               0
4               $               1               6
5               $               1               6
6               $               7               0
7               c               8               0
8               $               12              0
9               d               10              0
10              $               12              0
11              $               5               9
12              $               0               0

hiervan is de dot notatie ook gegeven:

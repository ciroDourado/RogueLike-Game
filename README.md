# RogueLike-Game

Pois bem, como diz a descrição, esse é um jogo de exploração que lembra muito aqueles antigos e adorados Roguelikes dos anos 80. Nele você é apenas um explorador que está numa caverna inexplorada, e está em busca de tesouros. Porém, deve tomar cuidado pois debaixo de algo valioso pode se esconder um monstro.
<br>
Deixando o plot um pouco de lado - visto que é apenas um simples jogo baseado nesse gênero - o que há de interessante em sua implementação é a geração randômica de mapas, e uma quantidade de níveis quase infinita. A minha primeira motivação para criar este jogo foi justamente para um projeto de faculdade, para a disciplina de estruturas de dados (em 2017). Eu escolhi este (dentre outros sobre grafos, ou jogos de tabuleiro) porque cresci jogando jogos que herdaram elementos dos Roguelike; e por ser um apreciador desde sempre, minha vontade de fazer um desses jogos também sempre foi muito grande.
<br>
Ele não chega a possuir uma IA (tanto que minha escolha para monstros foi um tanto quanto básica), e nem outros elementos que fazem deste jogo algo interessante comercialmente. Por ter sido um projeto de faculdade, fiquei limitado aos requisitos mínimos por conta do curto tempo para implementar.
<br>
Agora em 2021 decidi refazer do zero, refatorando boa parte dele e trazendo estruturas que se apliquem melhor ao contexto. Como você pode ver no diretório /original_2017, muita coisa (vulgo gambiarra) do que tem lá é reflexo de um programador pouco experiente ainda engatinhando nessa arte.
<br>
Meu desafio é usar as mesmas bibliotecas, ou menos. A principal, da qual não posso abrir mão, se chama tristto.h; a qual nos foi dada na época por nosso professor para auxiliar com toda a parte gráfica. Ela não é de minha autoria.
<br>
De resto, caso você queira testar o código/compilar e executar o jogo, você deve estar num sistema Windows (infelizmente não consegui fazer ele ser compatível com outros sistemas) que tenha o MinGW instalado juntamente com bibliotecas Posix (para que seja possível puxar funções de multithreading requeridas pela biblioteca tristto.h).

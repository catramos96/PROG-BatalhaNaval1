/*Trabalho nº1 - Batalha naval*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

struct Navio //Estrutura Navio
{
  int quant;
  string nome;
  int comprimento;
  char simbolo;
  string cor;
};

void LimparTabuleiro(vector<vector<char>> &tabuleiro, int nLinhasTab, int nColunasTab)
{
  for (int linha = 0; linha < nLinhasTab; linha++)
  {

    for (int coluna = 0; coluna < nColunasTab; coluna++)
    {
      tabuleiro[linha][coluna] = '.';
    }
  }
}

void MostrarTabuleiro(vector<vector<char>> &tabuleiro, int nLinhasTab, int nColunasTab)//Mostrar no ecra o tabuleiro
{
  int abc_coluna = int('a'); //passar para código ascii
  int abc_linha = int('A');
  cout << " ";
  for (int i = 0; i < nColunasTab; i++)
  {
    cout << " " << char(abc_coluna);  //Inserir caracteres em cima a cada coluna 
    abc_coluna = abc_coluna + 1;  //próximo caracter por ordem alfabetica
  }
  cout << endl;

  for (int linha = 0; linha < nLinhasTab; linha++)
  {
    cout << char(abc_linha);  //Inserir caracter em cada ínicio de linha
    abc_linha = abc_linha + 1;  //próximo caracter
    for (int coluna = 0; coluna < nColunasTab; coluna++)
      cout << " " << tabuleiro[linha][coluna];
    cout << endl;
  }
}

bool PosicaoValida(vector<vector<char>> tabuleiro, char posicaoLinha, char posicaoColuna, char orientacao, int comprimento, int simbolo, int nLinhasTab, int nColunasTab)
{
  int linha = int(posicaoLinha - 'A');
  int coluna = int(posicaoColuna - 'a');

  for (int i = 0; i < comprimento; i++)
  {
    if (linha > nLinhasTab || coluna > nColunasTab || linha < 0 || coluna < 0 || tabuleiro[linha][coluna] != '.') //Se não tiver entre as dimensões do tabuleiro ou se a posição já estiver ocupada com outro navio
    {
      return false;
    }
    else
    {
      if (orientacao == 'H')
        coluna = coluna + 1;
      else if (orientacao == 'V')
        linha = linha + 1;
    }
  }
  return true;
}

void PosicionarNavio(vector<vector<char>> &tabuleiro, char posicaoLinha, char posicaoColuna, char orientacao, int comprimento, int simbolo)
{
  int linha = int(posicaoLinha - 'A');
  int coluna = int(posicaoColuna - 'a');

  for (int i = 0; i < comprimento; i++)
  {
    tabuleiro[linha][coluna] = simbolo;
    if (orientacao == 'h' || orientacao == 'H')
      coluna = coluna + 1;
    else if (orientacao == 'v' || orientacao == 'V')
      linha = linha + 1;
  }
}

/*
LimparTabuleiro - faz um reset ao conteudo do tabuleiro e fica tudo preenchido com '.'
MostrarTabuleiro - Mostra o conteudo atual do tabuleir
PosicaoValida - devolve True/False conforme se a posicao for válida
PosicionarNavio - posiciona o Navio
*/

int main()
{
  //Adquirir os nomes dos ficheiros
  string nomeFichConfig, nomeFichTab;
  char modoFunc;


  cout << "Indique o nome do ficheiro de configuracao: ";
  cin >> nomeFichConfig;
  cout << "Indique o nome do ficheiro do tabuleiro: ";
  cin >> nomeFichTab;
  cout << "Indique o modo de funcionamento Automatico (A ou a) ou Manual (M ou m): ";
  cin >> modoFunc;
  cout << endl;



  //Ler conteudo do ficheiro de configuracao e guardar os navios num vector da struct navio

  fstream fichConfig;
  stringstream config;
  string linhaConfig, t, x; //t - palavra "tabuleiro"
  int nLinhasTab, nColunasTab; //Numero de linhas e colunas do tabuleiro
  vector<Navio> conjuntoNavios; //vector com structs de cada navio;
  Navio navio;
  char separador;


  fichConfig.open(nomeFichConfig);
  if (fichConfig.fail())
  {
    cout << "Ficheiro de configuracao inexistente! " << endl;
    return 1;
  }
  else
  {
    config.clear(); //limpar flags
    config.str(""); //limpar conteudo
    getline(fichConfig, linhaConfig); //Guarda a primeira linha do ficheiro
    config << linhaConfig;
    config >> t >> nLinhasTab >> x >> nColunasTab;
  }

  while (!fichConfig.eof()) //Repete até o ficheiro acabar
  {
    config.clear();
    config.str("");
    getline(fichConfig, linhaConfig);
    config << linhaConfig;
    config
      >> navio.quant >> separador
      >> navio.nome >> separador
      >> navio.comprimento >> separador
      >> navio.simbolo >> separador
      >> navio.cor;
    conjuntoNavios.push_back(navio);
  }
  fichConfig.close();


  //Gerar Tabuleiro Vazio
  vector<vector<char>> tabuleiro(nLinhasTab, vector<char>(nColunasTab));
  LimparTabuleiro(tabuleiro, nLinhasTab, nColunasTab);


  //Ciclo do jogo
  ofstream fichTab;
  char posicaoLinha, posicaoColuna, posicaoOrientacao;

  fichTab.open(nomeFichTab);

  fichTab << nLinhasTab << " x " << nColunasTab << endl;


  for (int i = 0; i < conjuntoNavios.size(); i++) //Passa por cada tipo de navio
  {
    while (conjuntoNavios[i].quant != 0) //Enquanto houver barcos do tipo conjuntoNavios[i]
    {
      MostrarTabuleiro(tabuleiro, nLinhasTab, nColunasTab); //Atualiza o tabuleiro

      cout << endl <<
        conjuntoNavios[i].simbolo << " - " << conjuntoNavios[i].nome << ". " <<
        "Tamanho: " << conjuntoNavios[i].comprimento << ". " <<
        "Falta(m): " << conjuntoNavios[i].quant << "." << endl << endl;
      

      if (modoFunc == 'm' || modoFunc == 'M')
      {
        do
        {
          cout << "Linha de A ... " << char(int('A') + (nLinhasTab - 1)) << " : ";
          cin >> posicaoLinha;
          cout << "Coluna de a ... " << char(int('a') + (nColunasTab - 1)) << " : ";
          cin >> posicaoColuna;
          cout << "Horizontal (H) ou Vertical (V): ";
          cin >> posicaoOrientacao;
          cout << endl;

        } while (!PosicaoValida(tabuleiro, posicaoLinha, posicaoColuna, posicaoOrientacao, conjuntoNavios[i].comprimento, conjuntoNavios[i].simbolo, nLinhasTab, nColunasTab));

        fichTab << conjuntoNavios[i].simbolo << " " << conjuntoNavios[i].comprimento << " " << posicaoLinha << posicaoColuna << " " << posicaoOrientacao << endl;
        PosicionarNavio(tabuleiro, posicaoLinha, posicaoColuna, posicaoOrientacao, conjuntoNavios[i].comprimento, conjuntoNavios[i].simbolo);
      }

      //Modo Automático
      else
      {
        do
        {
          int orient = rand() % 2; //orient = 1 -> Orientação = V, se = 0 -> Orientacao = H
          int random = rand() % 10;

          if (orient == 1)
          {
            posicaoOrientacao = 'V';
            posicaoLinha = char(random + 65 - conjuntoNavios[i].comprimento); //garante que nunca passará do tabuleiro
            posicaoColuna = char(random + 97);
          }
          else
          {
            posicaoOrientacao = 'H';
            posicaoLinha = char(random + 65);
            posicaoColuna = char(random + 97 - conjuntoNavios[i].comprimento); //garante que nunca passará do tabuleiro
          }

        } while (!PosicaoValida(tabuleiro, posicaoLinha, posicaoColuna, posicaoOrientacao, conjuntoNavios[i].comprimento, conjuntoNavios[i].simbolo, nLinhasTab, nColunasTab));
       
        PosicionarNavio(tabuleiro, posicaoLinha, posicaoColuna, posicaoOrientacao, conjuntoNavios[i].comprimento, conjuntoNavios[i].simbolo);
        fichTab << conjuntoNavios[i].simbolo << " " << conjuntoNavios[i].comprimento << " " << posicaoLinha << posicaoColuna << " " << posicaoOrientacao << endl;
      }
      conjuntoNavios[i].quant = conjuntoNavios[i].quant - 1;
    }   
  }

  MostrarTabuleiro(tabuleiro, nLinhasTab, nColunasTab); //Atualiza o tabuleiro

  fichTab.close();

  return 0;
}

/*NOTAS:
-Falta adicionar as cores
-Verificar Simbolo F dos Barcos
*/
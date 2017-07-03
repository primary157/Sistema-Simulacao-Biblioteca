/**
 * @file
 * @author "Victor Guerra Veloso e Luan Henrique Silva Alves"
 * @date "13/06/2017"
 * @brief Arquivo de Implementacao das funções do TAD modificado de Arvore B que faz uso de indexação 
 * por arquivos para leitura e escrita
 *
 * @details Nesse arquivo sobrescrevemos algumas funções básicas da implementação de Árvore B do Nivio Ziviani, 
 * dando a essa estrutura de dados a capacidade de gerenciar seus dados em arquivos de texto estruturados
 *
 * @copyright [GNU Public License 3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)
 */
/**
 * @mainpage Sistema Biblioteca
 * @section Intro_Section Introduction
 * Esse trabalho baseia-se na utilização da arvore B para a solução de um **problema real**. A dupla escolheu implementar um **sistema bibliotecário**
 * onde seria possível consultar o acervo, adicionar e pegar livros.
 * 
 * O código da Árvore B foi adquirido no livro do autor _Ziviani, N_. Os dados dos livros foram adquiridos em um arquivo de extensão _XLS_ de um acervo
 * de uma **biblioteca real** dos Estados Unidos, este foi convertido para a extensão _CSV_, no padrão europeu (a qual atende bem aos requisitos do sistema,
 * por ser compatível com nomes que possuem os caracteres espaço e virgula, sem interferir na interpretação deste, que separa cada item apenas por ";").
 * 
 * @section Plan_Section Fase de Planejamento
 * Nessa fase levantamos idéias para compor o desenvolvimento do sistema bibliotecário. Com as idéias em mente, nós filtramos o que seria possível e o que
 * não seria possível de implementar. Em seguida combinamos metas e prazos para cada tarefa, deixando sempre 2 tarefas em desenvolvimento simultâneo (1 tarefa
 * para cada integrante do grupo). 
 * 
 * Para nos organizarmos melhor decidimos que utilizaríamos algumas ferramentas que atendessem às nossas necessidades:
 * 
 * 1. **Trello**- Essa ferramenta foi muito útil para cada um acompanhar o progresso do outro e pedir ajuda/auxiliar um ao outro para as dificuldades que cada um foi encontrando;
 * 2. **GitHub**- Essa ferramenta serviu para que a última versão do programa estivesse sempre acessível pelo colega, além de servir como auxiliador para integrar
 * códigos distintos e voltar para versões antigas do código quando necessário.
 * 3. **Doxygen**- Essa ferramenta foi importante na criação da documentação e dos comentários do código.
 * 
 * @section Dev_Section Fase de Desenvolvimento
 * 
 * @subsection Org_Section Organização e metodologia utilizada
 * Como a parte de desenvolvimento era relativamente simples, demos ênfase em encontrar os exemplos para testes e encontrar os artigos antes de começar
 * a programar. Como as aula oferecidas para desenvolver o trabalho ocorriam algumas vezes em sala de aula(onde não possui acesso ao Wifi) e outras no
 * laboratório, preferimos reservar esses momentos para fazer perguntas sobre dúvidas que tivemos em reuniões passadas e para desenvolver outras coisas,reservando
 * assim a tarde para reunirmos e desenvolvermos em conjunto o trabalho num lugar de preferência do grupo. Apesar das reuniões serem presenciais, cada integrante
 * focava em desenvolver sua própria tarefa e, caso tivesse alguma dúvida, perguntava para o colega o que não soubesse.
 * 
 * @subsection Dif_Section Dificuldades Enfrentadas
 * Apesar do desenvolvimento ter tido um desempenho agradável não quer dizer que o grupo tenha desenvolvido o código sem nenhum impecilho. Muito pelo contrário,
 * dentre os problemas enfrentados podemos citar...
 * 
 * ...2 relacionados a interpretação da proposta do trabalho: 
 * 
 * 1. Como o trabalho exigia que referenciássemos pelo menos um artigo, interpretamos que nossa solução deveria basear-se em algo proposto por eles. 
 * O que descobrimos, ao conversar com a Professora Gláucia, ser apenas uma confusão do grupo.
 * 2. A proposta do trabalho mencionava a manipulação de arquivos e a implementação dos algoritmos de inserção, remoção e leitura da árvore B. O que pensamos se
 * referir ao desafio de adaptar o código do Ziviani para o uso da memória secundária, mas que mais tarde descobrimos se tratar apenas da interpretação de um
 * arquivo de entrada de dados
 * 
 * ...também podemos citar 2 relacionados ao desenvolvimento do código:
 * 
 * 1. um dos maiores desafios foi criar a biblioteca que viria a ser a CSVManager, responsável por interpretar o arquivo de entrada no formato CSV;
 * 2. outro grande desafio foi implementar a contagem de acessos à memória secundária sem realmente implementá-la.
 * 
 * ...e podemos citar um transtorno técnico inesperado:
 * 
 * 1. durante as primeiras semanas de desenvolvimento o carregador do notebook de um dos integrantes parou de funcionar o que travou o desenvolvimento por duas
 * semanas (tempo de entrega do novo carregador) porque todo o código desenvolvido na reunião do dia anterior se encontrava no notebook sem carga.
 * 
 * @subsection Sol_Section Soluções encontradas
 * Além dos problemas relacionados a interpretação da proposta do trabalho, os problemas encontrados durante o desenvolvimento também tiveram suas soluções
 * encontradas
 * @section Art_Section Artigos Escolhidos
 * @section Tes_Section Fase de Testes
 * @section Con_Section Considerações Finais
 */
#include "ArvoreDebugger.h"
#include "ArvoreBArquivo.h"
#include "Interface.h"
/**
 * @brief Função principal do programa, utlizada para testes e inicialização da interface 
 *
 *
 * Essa é a função principal e é por meio dela que serão executados os testes. Para isso essa função irá:
 *
 * 1. Ler o Arquivo
 * 2. Imprimir a Arvore resultante da leitura
 * 3. Testar validade da Arvore
 * 4. Rodar a interface de usuário para esse interagir com a aplicação
 */
int main()
{
  TipoApontador D;
  TipoPaginaDebugger *deb;
  LerArquivo(&D);
  Imprime(D);
  

  Testa(D);
  deb = PAGINADEBUGGER(D);
  run_ui(deb);
  return 0;
}



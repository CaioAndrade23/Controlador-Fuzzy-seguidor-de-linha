#include "FuzzyRule.h"
#include "FuzzyComposition.h" 
#include "Fuzzy.h"
#include "FuzzyRuleConsequent.h"
#include "FuzzyOutput.h"
#include "FuzzyInput.h"
#include "FuzzyIO.h"
#include "FuzzySet.h"
#include "FuzzyRuleAntecedent.h"

// Instanciando um objeto da biblioteca
Fuzzy* fuzzy = new Fuzzy();// criando um novo sistema fuzzy sem senhum paremetro 

  //------------------------------------------------------------------------------------------Modelagem das funções de pertinência 
  
// setando um trapezio onde o primeiro ponto é o inicial (0), o segundo é ate onde entre o primeiro ponto é o segundo ele ira variar ate (1)
// o terçeiro é ate onde o segundo ponto é o terçeiro ira manter em (1)e o quarto é ate onde ele vai variar do terçeiro ate o quarto ponto há (0)

//criando os trapézios que seram as funções de pertinência de entrada os graficos que estão associadas as entradas do fuzzy
FuzzySet* AchouMuitoEsquerda = new FuzzySet(-0.9, 0.1, 0.1, 0.1);
FuzzySet* AchouEsquerda = new FuzzySet(-0.1, 0.9 ,0.9, 0.9);
FuzzySet* AchouIdeal = new FuzzySet(0, 0 , 0, 0);
FuzzySet* AchouDireita = new FuzzySet(-0.1, 0.9, 0.9, 0.9);
FuzzySet* AchouMuitoDireita= new FuzzySet(-0.9, 0.1, 0.1, 0.1);
FuzzySet* PerdeuMuitoEsquerda = new FuzzySet(1, 1, 1, 1);
FuzzySet* PerdeuEsquerda = new FuzzySet(1, 1, 1, 1);
FuzzySet* PerdeuIdeal = new FuzzySet(1, 1, 1, 1);
FuzzySet* PerdeuDireita = new FuzzySet(1, 1, 1, 1);
FuzzySet* PerdeuMuitoDireita= new FuzzySet(1, 1, 1, 1);






//iniciando a função principal 
int main(){
// definindo os canais de leitura (da extrema esquerda ate a extrema direita)
 int S1,S2,S3,S4,S5;
//################################## inicio da configuracao do PWM #######
    
    //configurando  modo PWM  (fase corrigida, 10 bits) do temporizador/contador TC1  que é conectado aos pinos OC1A (PB1) -> D9 e OC1B (PB2)-> D10
    
    //TC1 é um contador de 16 bits que permite grande precisão na geração de formas de onda
    
    //#################################
    //O controle do modo de operação do TC1 é feito nos registradores  TCCR1A e TCCR1B
    
    TCCR1A = ((1 << COM1A1)  | ((1 << COM1B1) | (1 << WGM11) | (1 << WGM10)));
    //WGM11 e WGM10 configura o modo de operacao 3 do TC1 como fase corrigida, 10 bits
    //COM1A1 e COM1B1 Limpeza de OC1A/OC1B na igualdade de comparação, isso define um PWM nao invertido
    
    TCCR1B =  (1 << CS10);
    //CCS12, CCS11 e CCS10 seleção do clock para o TC1.
    
    //CCS11 e CCS10 clock/64
 
    
    //################################## fim da configuracao do PWM #######


//################################## inicio da configuracao das portas que serao usadas #######
    DDRB=((1 <<  PB1)  |  (1 <<  PB2)); //define pino D9 e D10 com saida
    
    DDRD=((0 <<  PD2)  |  (0 <<  PD4)  |  (0 <<  PD5)  |  (0 <<  PD6)  | (0 <<  PD7));// define os pinos d2 d4 d5 d6 d7 com entrada
    //################################## fim da configuracao das portas que serao usadas #######
    
  //------------------------------------------------------------------------------------------Declarando as entradas do sistema

  
  FuzzyInput* MuitoEsquerda = new FuzzyInput(1);// criando a entrada em Fuzzy chamada MuitoEsquerda e está é a primeira entrada (1)
  MuitoEsquerda->addFuzzySet(AchouMuitoEsquerda);// na entrada MuitoEsquerda adicionou o grafico (função de pertinencia AchouMuitoEsquerda)
  MuitoEsquerda->addFuzzySet(PerdeuMuitoEsquerda);// na entrada MuitoEsquerda adicionou o grafico (função de pertinencia PerdeuMuitoEsquerda)
  fuzzy-> addFuzzyInput(MuitoEsquerda);// adicionou ao sistema fuzzy a entrada MuitoEsquerda

  FuzzyInput* Esquerda = new FuzzyInput(2);// criando a entrada em Fuzzy chamada Esquerda e está é a segunda entrada (2)
  Esquerda->addFuzzySet(AchouEsquerda);// na entrada Esquerda adicionou o grafico (função de pertinencia AchouEsquerda)
  Esquerda->addFuzzySet(PerdeuEsquerda);// na entrada Esquerda adicionou o grafico (função de pertinencia PerdeuEsquerda)
  fuzzy-> addFuzzyInput(Esquerda);// adicionou ao sistema fuzzy a entrada Esquerda

  FuzzyInput* Ideal = new FuzzyInput(3);// criando a entrada em Fuzzy chamada Ideal e está é a Terçeira entrada (3)
  Ideal->addFuzzySet(AchouIdeal);// na entrada Ideal adicionou o grafico (função de pertinencia AchouIdeal)
  Ideal->addFuzzySet(PerdeuIdeal);// na entrada Ideal adicionou o grafico (função de pertinencia PerdeuIdeal)
  fuzzy->addFuzzyInput(Ideal);// adicionou ao sistema fuzzy a entrada Ideal

  FuzzyInput* Direita = new FuzzyInput(4);// criando a entrada em Fuzzy chamada Direita e está é a Quarta entrada (4)
  Direita->addFuzzySet(AchouDireita);// na entrada Direita adicionou o grafico (função de pertinencia AchouDireita)
  Direita->addFuzzySet(PerdeuDireita);// na entrada Direita adicionou o grafico (função de pertinencia PerdeuDireita)
  fuzzy-> addFuzzyInput(Direita);// adicionou ao sistema fuzzy a entrada Direita

  FuzzyInput* MuitoDireita = new FuzzyInput(5);// criando a entrada em Fuzzy chamada MuitoDireita e está é a Quinta entrada (5)
  MuitoDireita->addFuzzySet(AchouMuitoDireita);// na entrada MuitoDireita adicionou o grafico (função de pertinencia AchouMuitoDireita)
  MuitoDireita->addFuzzySet(PerdeuMuitoDireita);// na entrada MuitoDireita adicionou o grafico (função de pertinencia PerdeuMuitoDireita)
  fuzzy-> addFuzzyInput(MuitoDireita);// adicionou ao sistema fuzzy a entrada MuitoDireita

//-----------------------------------------------------------------------------------------------------Declarando as saidas 

//-----------------------------------------------------------------------------------------------------saída 1
FuzzyOutput* MotorEsquerdo = new FuzzyOutput(1);//Criando a saída em Fuzzy MotorEsquerdo e está é a primeira saída(1)
FuzzySet* TensaoMotorEsquerdo = new FuzzySet(0,600,600,600); //Criando um grafico (Função de pertinência) trapezoidal 
FuzzySet* TensaoMotorEsquerdo2 = new FuzzySet(0,0,0,160);    //Criando um grafico (Função de pertinência) trapezoidal
FuzzySet* TensaoMotorEsquerdo3 = new FuzzySet(0,0,361,361);  //Criando um grafico (Função de pertinência) trapezoidal
FuzzySet* TensaoMotorEsquerdo4 = new FuzzySet(0,400,400,400);//Criando um grafico (Função de pertinência) trapezoidal
MotorEsquerdo->addFuzzySet(TensaoMotorEsquerdo);  //Adicionando a saída MotorEsquerdo o grafico(Função de pertinência) TensaoMotorEsquerdo
MotorEsquerdo->addFuzzySet(TensaoMotorEsquerdo2); //Adicionando a saída MotorEsquerdo o grafico(Função de pertinência) TensaoMotorEsquerdo2
MotorEsquerdo->addFuzzySet(TensaoMotorEsquerdo3); //Adicionando a saída MotorEsquerdo o grafico(Função de pertinência) TensaoMotorEsquerdo3
MotorEsquerdo->addFuzzySet(TensaoMotorEsquerdo4); //Adicionando a saída MotorEsquerdo o grafico(Função de pertinência) TensaoMotorEsquerdo4
fuzzy ->addFuzzyOutput(MotorEsquerdo); //Adicionando ao sistema Fuzzy a saída MotorEsquerdo

//------------------------------------------------------------------------------------------------------saida 2 

FuzzyOutput* MotorDireito = new FuzzyOutput(2); //Criando a saída em Fuzzy MotorDireito e está é a segunda saída
FuzzySet* TensaoMotorDireito = new FuzzySet(0,0,0,160);     //Criando um grafico (Função de pertinência) trapezoidal
FuzzySet* TensaoMotorDireito2 = new FuzzySet(0,600,600,600);//Criando um grafico (Função de pertinência) trapezoidal
FuzzySet* TensaoMotorDireito3 = new FuzzySet(0,0,360,360);  //Criando um grafico (Função de pertinência) trapezoidal
FuzzySet* TensaoMotorDireito4 = new FuzzySet(0,40,400,400); //Criando um grafico (Função de pertinência) trapezoidal
MotorDireito->addFuzzySet(TensaoMotorDireito);  //Adicionando a saída MotorDireito o grafico(Função de pertinência) TensaoMotorDireito
MotorDireito->addFuzzySet(TensaoMotorDireito2); //Adicionando a saída MotorDireito o grafico(Função de pertinência) TensaoMotorDireito2
MotorDireito->addFuzzySet(TensaoMotorDireito3); //Adicionando a saída MotorDireito o grafico(Função de pertinência) TensaoMotorDireito3
MotorDireito->addFuzzySet(TensaoMotorDireito4); //Adicionando a saída MotorDireito o grafico(Função de pertinência) TensaoMotorDireito4
fuzzy ->addFuzzyOutput(MotorDireito); //Adicionando ao sistema Fuzzy a saída MotorDireito

//--------------------------------------------------------------------------------------Composição das regras: Condições de ativação e qual será a consequência
//-------------------------------------------------------------------------------------------------------Caso somente s1 seja ativado---> regra 1
  
  FuzzyRuleAntecedent* AchouMuitoEsquerdaAndPerdeuResto= new FuzzyRuleAntecedent();//Criando a regra antecedente(que usa dados diretamente ligados a entrada) chamada AchouMuitoEsquerdaAndPerdeuResto
  AchouMuitoEsquerdaAndPerdeuResto->joinSingle(AchouMuitoEsquerda); // Adicionando a regra criada um grafico sem nenhuma Condição (joinSingle) apenas dizendo que quando o valor estiver dentro do intervalo AchouMuitoEsquerda esta regra estara valendo
  
  FuzzyRuleConsequent* thenAchouMuitoEsquerdaAndPerdeuResto = new FuzzyRuleConsequent();//Criando a regra Consequent (Que liga dados diretamente a saída do Fuzzy) chamada thenAchouMuitoEsquerdaAndPerdeuResto
  thenAchouMuitoEsquerdaAndPerdeuResto->addOutput(TensaoMotorDireito2);//Adicionando a regra a ao grafico (Função de pertinência) TensaoMotorDireito2, então quando esta regra for ativa ira jogar a resposta em TensaoMotorDireito2
  thenAchouMuitoEsquerdaAndPerdeuResto->addOutput(TensaoMotorEsquerdo2); //Adicionando a regra a ao grafico (Função de pertinência) TensaoMotorEsquerdo2, então quando esta regra for ativa ira jogar a resposta em TensaoMotorDEsquerdo2

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1,AchouMuitoEsquerdaAndPerdeuResto,thenAchouMuitoEsquerdaAndPerdeuResto);//Criando a regra em si esta é a primeira regra e associa a regra antecedente AchouMuitoEsquerdaAndPerdeuResto que se for ativada ira ativar a regra consequent thenAchouMuitoEsquerdaAndPerdeuResto
  fuzzy->addFuzzyRule(fuzzyRule1);// Adicionando ao sistema Fuzzy a regra fuzzyRule1 e esta é a primeira regra criada

 //------------------------------------------------------------------------------------------------------Caso somente s2 seja ativado---> regra 2
// está regra segue a mesma ideia da regra 1 
  FuzzyRuleAntecedent* AchouEsquerdaAndPerdeuResto = new FuzzyRuleAntecedent();
  AchouEsquerdaAndPerdeuResto->joinSingle(AchouEsquerda);

  FuzzyRuleConsequent* thenAchouEsquerdaAndPerdeuResto = new FuzzyRuleConsequent();
  thenAchouEsquerdaAndPerdeuResto->addOutput(TensaoMotorDireito4);
  thenAchouEsquerdaAndPerdeuResto->addOutput(TensaoMotorEsquerdo2);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2,AchouEsquerdaAndPerdeuResto, thenAchouEsquerdaAndPerdeuResto);
  fuzzy->addFuzzyRule(fuzzyRule2);

//-------------------------------------------------------------------------------------------------------Caso somente s3 seja ativado---> regra 3 
// está regra segue a mesma ideia da regra 1 
  FuzzyRuleAntecedent* AchouIdealAndPerdeuResto = new FuzzyRuleAntecedent();
  AchouIdealAndPerdeuResto->joinSingle(AchouIdeal);
  
  FuzzyRuleConsequent* thenAchouIdealAndPerdeuResto = new FuzzyRuleConsequent();
  thenAchouIdealAndPerdeuResto->addOutput(TensaoMotorDireito3);
  thenAchouIdealAndPerdeuResto->addOutput(TensaoMotorEsquerdo3);
  
  FuzzyRule* fuzzyRule3 = new FuzzyRule(3,AchouIdealAndPerdeuResto, thenAchouIdealAndPerdeuResto);
  fuzzy->addFuzzyRule(fuzzyRule3);

//-------------------------------------------------------------------------------------------------------Caso somente s4 seja ativado---> regra 4
// está regra segue a mesma ideia da regra 1 
  
  FuzzyRuleAntecedent* AchouDireitaAndPerdeuResto = new FuzzyRuleAntecedent();
  AchouDireitaAndPerdeuResto->joinSingle(AchouDireita);
  
  FuzzyRuleConsequent* thenAchouDireitaAndPerdeuResto = new FuzzyRuleConsequent();
  thenAchouDireitaAndPerdeuResto->addOutput(TensaoMotorDireito);
  thenAchouDireitaAndPerdeuResto->addOutput(TensaoMotorEsquerdo4);
  
  FuzzyRule* fuzzyRule4 = new FuzzyRule(4,AchouDireitaAndPerdeuResto,thenAchouDireitaAndPerdeuResto);
  fuzzy->addFuzzyRule(fuzzyRule4);

 //------------------------------------------------------------------------------------------------------Caso somente s5 seja ativado---> regra 5
 // está regra segue a mesma ideia da regra 1 
  
  FuzzyRuleAntecedent* AchouMuitoDireitaAndPerdeuResto = new FuzzyRuleAntecedent();
  AchouMuitoDireitaAndPerdeuResto->joinSingle(AchouMuitoDireita);
  
  FuzzyRuleConsequent* thenAchouMuitoDireitaAndPerdeuResto = new FuzzyRuleConsequent();
  thenAchouMuitoDireitaAndPerdeuResto->addOutput(TensaoMotorDireito);
  thenAchouMuitoDireitaAndPerdeuResto->addOutput(TensaoMotorEsquerdo);
  
  FuzzyRule* fuzzyRule5 = new FuzzyRule(5,AchouMuitoDireitaAndPerdeuResto, thenAchouMuitoDireitaAndPerdeuResto);
  fuzzy->addFuzzyRule(fuzzyRule5);
//----------------------------------------------------------------------------------------------------------------Regras adicionais
//----------------------------------------------------------------------------------------------------------------Todos sensores detectando branco(1)

 
  FuzzyRuleAntecedent* PerdeuMuitoDireitaAndDireita = new FuzzyRuleAntecedent();//criando uma regra antecedente
  PerdeuMuitoDireitaAndDireita->joinWithAND(PerdeuMuitoDireita, PerdeuDireita);//Adicionando a regra antecedente criada na linha anterior duas entradas atraves da operação joinWithAND que ira pegar o menor valor entra as duas entradas
  FuzzyRuleAntecedent* PerdeuMuitoEsquerdaAndEsquerda= new FuzzyRuleAntecedent();//criando uma nova regra antecedente
  PerdeuMuitoEsquerdaAndEsquerda->joinWithAND(PerdeuMuitoEsquerda, PerdeuEsquerda);//Adicionando a regra antecedente criada na linha anterior duas entradas atraves da operação joinWithAND que ira pegar o menor valor entra as duas entradas
  FuzzyRuleAntecedent* PerdeuSensoresLaterais = new FuzzyRuleAntecedent();//criando uma nova regra antecedente
  PerdeuSensoresLaterais->joinWithAND(PerdeuMuitoDireitaAndDireita, PerdeuMuitoEsquerdaAndEsquerda);//Adicionando a regra antecedente criada na linha anterior as duas regras antecedentes anteriores que atraves da operação joinWithAND que ira pegar o menor valor entra as duas 
  FuzzyRuleAntecedent* PerdeuTudo= new FuzzyRuleAntecedent();//Criando uma nova regra antecedente
  PerdeuTudo->joinWithAND(PerdeuSensoresLaterais, PerdeuIdeal);//Adicionando a regra antecedente criada na linha anterior as duas regras antecedentes anteriores que atraves da operação joinWithAND que ira pegar o menor valor entra as duas

  FuzzyRuleConsequent* thenPerdeuTudo = new FuzzyRuleConsequent();//Criando a regra consequent
  thenPerdeuTudo->addOutput(TensaoMotorDireito3);//adicionando a regra consequent ao grafico (Função de pertinencia) TensaoMotorDireito3
  thenPerdeuTudo->addOutput(TensaoMotorEsquerdo3);//adicionando a regra consequent ao grafico (Função de pertinencia) TensaoMotorEsquerdo3

  FuzzyRule* fuzzyRule6 = new FuzzyRule(6, PerdeuTudo, thenPerdeuTudo);//Criando a sexta regra que sera ativa com o valor de PerdeuTudo e este valor sera associado ao thenPerdeuTudo
  fuzzy->addFuzzyRule(fuzzyRule6);//Adicionando a sexta Regra ao sistema Fuzzy

  //----------------------------------------------------------------------------------------------------------------Todos sensores detectando preto(0) ou nada 
 
// Laço de repetição para que o seguidor sempre faça a leitura dos sensores 
while(1){
  
  
  int SaidaMotorEsquerdo;// criando a variavel inteira que ira armazenar a saida para o motor esquerdo
  int SaidaMotorDireito;// criando a variavel inteira que ira armazenar a saida para o motor Direito
 
  
      bool C1,C2,C3,C4,C5;// criando variaveis booleanas que irão ajudar na logica para leitura
    // ################ INICIO #### Leitura digital dos sensores #################
    if(PIND & (1<<PD7)) {//leitura digital do pino d7
        C1 = 1;}
    else {C1 = 0;}
    
    
    if(PIND & (1<<PD6)) {//leitura digital do pino d6
        C2 = 1;}
    else {C2 = 0;}
    
    
    if(PIND & (1<<PD5)) {//leitura digital do pino d5
        C3 = 1;}
    else {C3 = 0;}
    
    
    if(PIND & (1<<PD4)) {//leitura digital do pino d4
        C4 = 1;}
    else {C4 = 0;}
    
    
    if(PIND & (1<<PD2)) {//leitura digital do pino d2
        C5 = 1;}
    else {C5 = 0;}
    
    // ################ FIM #### Leitura digital dos sensores #################
   
   
   
   
  fuzzy->setInput(1,C1);//Adicionando ao sistema Fuzzy na primeira entrada o valor armazenado em C1
  fuzzy->setInput(2,C2);//Adicionando ao sistema Fuzzy na segunda entrada o valor armazenado em C2
  fuzzy->setInput(3,C3);//Adicionando ao sistema Fuzzy na terçeira entrada o valor armazenado em C3
  fuzzy->setInput(4,C4);//Adicionando ao sistema Fuzzy na quarta entrada o valor armazenado em C4
  fuzzy->setInput(5,C5);//Adicionando ao sistema Fuzzy na quinta entrada o valor armazenado em C5
  fuzzy->fuzzify();//Mandando o comando para que o sistema Fuzzy seja executado

  
  SaidaMotorEsquerdo = fuzzy->defuzzify(1);// Defuzzificando e "colhendo" a saída 1 do sistema fuzzy e armazenando em SaidaMotorEsquerdo
  SaidaMotorDireito = fuzzy->defuzzify(2);// Defuzzificando e "colhendo" a saída 2 do sistema fuzzy e armazenando em SaidaMotorDireito

  OCR1A = 2 * SaidaMotorDireito; //e1screve o valor de 0 a 1023 no pino d9
  OCR1B = 2 * SaidaMotorEsquerdo; //escreve o valor de 0 a 1023 no pino d10
 


//laço de repetição para caso nenhum sensor seja lido (isto ira ajudar com que o carrinho faça curva armazenando o ultimo valor do erro gerado pelo sistema fuzzy e o congelando fazendo com que
//o carrinho continue fazendo a curva mesmo sem ler nenhum sensor, isto foi nescessario pois a leitura dos sensores é muito ruim) então apenas quando todos os sensores derem 1 que esse while sera ativado
 while((PIND & (1<<PD7)) &&   (PIND & (1<<PD6))  && (PIND & (1<<PD5)) &&  (PIND & (1<<PD4)) && (PIND & (1<<PD2)) ){
  // aqui o valor em C1-C5 é o mesmo do ultimo ciclo de fuzzy então ele ira jogar este mesmo falor para ser executado e assim retornando a mesma resposta
  // foi nescessario refazer todo o processo pois se não fosse feito o código apresentava problemas e não funcionada adequadamente
  fuzzy->setInput(1,C1);
  fuzzy->setInput(2,C2);
  fuzzy->setInput(3,C3);
  fuzzy->setInput(4,C4);
  fuzzy->setInput(5,C5);
  fuzzy->fuzzify();
  SaidaMotorEsquerdo = fuzzy->defuzzify(1);
  SaidaMotorDireito = fuzzy->defuzzify(2);
  
  OCR1A = 2 * SaidaMotorDireito; //escreve o valor de 0 a 1023 no pino d9
  OCR1B = 2 * SaidaMotorEsquerdo; //escreve o valor de 0 a 1023 no pino d10
  
  
 }

 
  
 
  

  }
}

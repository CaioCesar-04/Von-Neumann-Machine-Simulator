# Von-Neumann-Machine-Simulator

Este projeto tem como objetivo a implementação de um simulador de CPU com conjunto de instruções (ISA - Instruction Set Architecture), conjunto de registradores arquiteturais e formato de instrução específicos. A implementação deve ser realizada em linguagem C e a memória deve ser um vetor de palavras de oito bits de 154 posições. Todas as transferências entre o MBR (Memory Buffer Register) e a memória devem ser feitas de byte em byte, utilizando um barramento de oito bits.

A CPU a ser implementada processa palavras de 16 bits contendo apenas números inteiros, sem operações com ponto-flutuante ou aritmética sinalizada. Embora o formato de instrução permita endereçar até 2^11 = 2.048 palavras de oito bits na memória, a memória possui apenas 154 endereços, de 0 (0x0) a 153 (0x99).

O simulador deve ser capaz de ler um arquivo texto para carregar a memória com instruções e dados, e deve apresentar o conteúdo dos registradores ao final de cada ciclo de máquina. Para facilitar a compilação e uso do programa, instruções de compilação e uso do programa devem ser fornecidas.

É importante lembrar que o código-fonte necessário para a compilação e o programa compilado devem ser entregues, assim como instruções de compilação e de uso do programa.

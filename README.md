
# Semáforo utilizando temporizador periódico

Este repositório contém o projeto de controle de Animações em um display OLED bem como em uma matriz de LEDs 5x5 e um LED RGB.

## Componentes
- Microcontrolador Raspberry Pi Pico W.
- 03 LEDs (vermelho, amarelo e verde).
- Matriz de LEDs 5x5
- Display OLED 128x64
- 02 botões

## Funcionamento

- Envia-se por parte do usuário caracteres via serial monitor, e estes caracteres são exibidos no display OLED, quando um caractere inserido for um número, ele deve ser representado também na matriz de LED 5x5
- Ao apertar o botão A, ele acende/apaga o LED Verde, ao apertar o botão B, ele acende/apaga o LED Azul, ambas modificações são apresentadas no serial monitor e também no display OLED.
  
## Instruções de uso

### Requisitos
- Ambiente de desenvolvimento **VS Code**.
- **Simulador Wokwi** para simulação do hardware.
- Kit de desenvolvimento **Pico SDK**.

### Passos para Execução
1. Clone este repositório:
   ```bash
   git clone https://github.com/andrelimatecnologias/tarefa_u4c6_interfaces_seriais.git
   ```
2. Instale as dependências necessárias para o Pico SDK.
3. Importe o projeto no **VS Code** e configure o simulador Wokwi.
4. Compile o código
5. Coloque a placa em modo Bootsel e transfira o código para iniciar a aplicação ao testar na placa BitDogLab
6. Inicialize o serial monitor e introduza os caracteres para acompanhar a exibição no display OLED e também na matriz de LED 5x5 (Caso seja um número)
7. Pressione os botões e veja o controle dos LEDs e as informações apresentadas no serial monitor e no display OLED.

### Observação
A prática pode ser realizada apenas em hardware real.

## Vídeo de teste
Um vídeo mostrando o teste desta atividade pode ser acessado no link: https://youtu.be/KkeTpDVYV28

## Autor do projeto:
André Souza Lima

# WorkFlow Adaptive System (WAS)
## Integrantes do Grupo

| Nome Completo | RM |
| :--- | :--- |
| Jonas Kimio Isiki | 560560 |
| Daniel Kendi Saijo Araki | 553043 |
| Marcos Vinicius Alves Marques | 560475 |
---

## 1. Informações do Projeto

| Item | Detalhe |
| :--- | :--- |
| **Disciplina** | DISRUPTIVE ARCHITECTURES: IOT, IOB & GENERATIVE IA |
| **Tema** | O Futuro do Trabalho / Bem-Estar e Produtividade em Home Office |
| **Gateway Utilizado** | Node-RED (para Processamento, Lógica Disruptiva e Dashboard) |
| **Protótipo** | ESP32 (Simulado no Wokwi) com sensores DHT (Temperatura) e MQ-135 (Qualidade do Ar) |
| **Status do Dashboard** | **Funcional (Node-RED Dashboard)** |
| **Link do Vídeo** | [INSERIR LINK DO VÍDEO NO YOUTUBE AQUI] |

---

## 2. Descrição Completa da Solução e Finalidade

O **WorkFlow Adaptive System (WAS)** é uma solução de IoT aplicada ao tema **O Futuro do Trabalho**, com foco na melhoria do **bem-estar e produtividade** em ambientes de trabalho remoto.

A solução integra coleta de dados ambientais com uma **Lógica Disruptiva** baseada no conceito de **Internet of Behaviors (IoB)**:

1.  **Monitoramento:** O sistema coleta dados de **temperatura** e **qualidade do ar** (PPM) do ambiente.
2.  **Lógica Disruptiva:** Quando a **qualidade do ar cai para níveis ruins** (poluentes acima de 500 PPM), o sistema intervém de forma proativa.
3.  **Ação Sugerida:** O Gateway dispara um alerta via **HTTP POST** sugerindo uma **"Pausa para Planejamento de Curso sobre Ergonomia"**. Essa ação interage conforme a necessidade do cenário (qualidade do ar), cumprindo o requisito de execução de ações.

---

## 3. Protótipo Funcional e Código

O protótipo é simulado no **Wokwi**, comprovando a funcionalidade da solução IoT.

### 3.1. Código-Fonte

O código-fonte (`/wokwi/main.ino`) está **organizado e totalmente comentado**, cobrindo o requisito de código-fonte.

* **Comunicação:** O ESP32 utiliza o protocolo **MQTT** para comunicação assíncrona com o Gateway.
* **Mensagem:** O payload é formatado no padrão **JSON** e enviado no tópico exclusivo `fiap/gs/workflow/sensor01`.

### 3.2. Link do Protótipo

* **Link da Simulação no Wokwi:** [INSERIR O LINK DO SEU PROJETO WOKWI AQUI]

---

## 4. Gateway (Node-RED)

O Node-RED cumpre os requisitos de **Gateway** (processamento de dados) e **Dashboard** (visualização e controle).

### 4.1. Configuração e Importação

1.  **Instalação:** Certifique-se de que o `node-red-dashboard` esteja instalado (Instruções: `npm install -g node-red-dashboard`).
2.  **Inicialização:** Inicie o Node-RED (`node-red`).
3.  **Importação do Fluxo:** Importe o conteúdo do arquivo **`/node-red/WAS_Flow.json`** no editor.
4.  **Dashboard:** O painel de monitoramento em tempo real está acessível em: `http://localhost:1880/ui`.

### 4.2. Registro e Explicação dos Fluxos

O fluxo é dividido em três ramificações principais após a decodificação dos dados (Registro do Fluxo):

| Nó / Etapa | Função e Requisito |
| :--- | :--- |
| **MQTT / JSON Parser** | **Recepção de Dados:** Recebe a mensagem do Wokwi (Protocolo **MQTT**) e decodifica o payload (Protocolo **JSON**). |
| **Extract Temp / Qualidade do Ar** | **Dashboard:** Extrai os valores e os exibe nos medidores (`ui_gauge`) no Dashboard, provando o **Monitoramento em tempo real**. |
| **Interruptor: Ar Ruim > 500ppm** | **Lógica Disruptiva:** O núcleo da inteligência. Checa a condição crítica: `payload.air_quality_ppm > 500`. Se **verdadeiro**, aciona a ação de alerta. |
| **HTTP POST: Alerta Carreira** | **Ação (Protocolo HTTP):** Envia o alerta formatado via **HTTP POST** para um endpoint simulado, comprovando a execução de ações e o uso do protocolo HTTP. |

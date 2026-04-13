# 🏦 BM-Bank: Sistema de Gestão de Usuários

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Terminal](https://img.shields.io/badge/Console-Black?style=for-the-badge&logo=gnu-bash&logoColor=white)

Um sistema bancário interativo via console desenvolvido puramente em C++. O grande diferencial deste projeto é a utilização **100% de alocação dinâmica de memória**, sem depender de bibliotecas padrão como `std::vector`. O sistema gerencia um vetor de structs de usuários que se redimensiona automaticamente conforme a necessidade.

---

## ✨ Funcionalidades

O sistema conta com um menu interativo completo para o gerenciamento de contas:

* **Cadastro Dinâmico:** Inserção de um ou múltiplos usuários simultaneamente.
* **Sistema de IDs:** Geração e controle automático de Identificadores Únicos (IDs) para cada conta.
* **Operações Bancárias:** Transferência de saldo entre contas registradas com validação de saldo insuficiente.
* **Busca e Remoção:** Consulta rápida de dados por ID e exclusão de contas do sistema.
* **Persistência de Dados:** Salvamento automático e carregamento de usuários através de arquivos de texto (`BmBank.txt`).

---

## 🛠️ Detalhes Técnicos (Under the Hood)

Para fins acadêmicos e de aprofundamento em C++, o projeto implementa conceitos fundamentais da linguagem:

* **Alocação Dinâmica (`new` / `delete[]`):** A capacidade do vetor de usuários (`User* usuarios`) dobra automaticamente quando o limite é atingido (lógica implementada na função `garantirCapacidade()`).
* **Manipulação de Arquivos (`<fstream>`):** Leitura de strings particionadas (parsing de `.csv` manual) utilizando `find`, `substr` e conversões (`stoi`, `stod`).
* **Gerenciamento de Ponteiros e Memória:** Prevenção de *memory leaks* garantindo que os arrays antigos sejam deletados ao redimensionar e ao encerrar o programa.

---

## 📂 Estrutura do Projeto

📦 Sistema-de-Gestao-de-Usuarios-do-BM-Bank
 ┣ 📜 Bm-Bank.cpp        # Código fonte principal com toda a lógica
 ┣ 📜 BmBank.txt         # Arquivo gerado automaticamente para salvar os dados
 ┗ 📜 README.md          # Documentação

---

## 🚀 Como Executar

Para compilar e testar o projeto localmente, você precisará de um compilador C++ (como o GCC/MinGW).

**1. Clone o repositório:**
> git clone https://github.com/ThierryTorino/Sistema-de-Gestao-de-Usuarios-do-BM-Bank.git

**2. Compile o código:**
> g++ Bm-Bank.cpp -o bmbank

**3. Execute o programa:**

* No Windows:
> ./bmbank.exe

* No Linux/macOS:
> ./bmbank

**Observação:** Ao rodar o programa pela primeira vez, ele tentará carregar o `BmBank.txt`. Se o arquivo não existir, o sistema o criará automaticamente ao escolher a opção "Sair e Salvar" (`0`) no menu.

---

Feito por **[Thierry Torino]**

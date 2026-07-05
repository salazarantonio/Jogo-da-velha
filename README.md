# Jogo da Velha em C

Este repositório contém o projeto desenvolvido para a disciplina de **Programação Estruturada**, como parte da grade do curso de **Ciência de Dados e Inteligência Artificial** da **UFPB**.

## 📝 Sobre o Projeto

> **Nota:** O projeto é um jogo da velha desenvolvido em linguagem C, com três fases progressivas de complexidade.

O objetivo principal foi aplicar na prática os conceitos de programação estruturada em C, como modularização de código, structs, ponteiros e comunicação entre processos via rede.

## 🚀 Fases do Projeto

* **Fase 1** — Jogo entre dois jogadores locais pelo teclado — ✅ Concluída ([`1x1`](./1x1))
* **Fase 2** — Jogo local contra Inteligência Artificial — ✅ Concluída ([`Offline`](./Offline))
* **Fase 3** — Jogo entre dois jogadores via servidor — ⏳ Pendente

## 🛠️ Tecnologias Utilizadas

* [C (GCC)](https://gcc.gnu.org/)

## 👥 Integrantes da Equipe

Este projeto foi construído colaborativamente por:

* **Antonio Salazar** - [GitHub](https://github.com/salazarantonio)
* **Igor Barbosa** - [GitHub](https://github.com/igorbarbosaro-art)

## ⚙️ Como Executar na Sua Máquina

Siga os passos abaixo para rodar o jogo localmente:

1. Clone este repositório:
```bash
   git clone https://github.com/salazarantonio/Jogo-da-velha.git
```

2. Acesse a pasta da fase que deseja executar:
```bash
   cd Jogo-da-velha/1x1       # Fase 1 - dois jogadores
   # ou
   cd Jogo-da-velha/Offline   # Fase 2 - contra a IA
```

3. Compile o projeto:
```bash
   gcc main.c def.c -o jogo
```

4. Execute o jogo:
```bash
   ./jogo
```

---

📅 *Projeto acadêmico - 2026*
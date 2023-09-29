# Buteco do Geraldo

## Descrição

O Buteco do Geraldo é um sistema desenvolvido, para fins acadêmicos durante as aulas de estrutura de dados e programação, para auxiliar na gestão eficiente de um boteco, permitindo que os proprietários e funcionários gerenciem os itens de estoque, vendas e relatórios de forma conveniente e eficaz.

## Funcionalidades

### Adicionar Item

Os usuários podem adicionar novos itens ao estoque, especificando detalhes como número identificador, nome, quantidade inicial, data de entrada e preço de venda.

### Remover Item

Itens que não fazem mais parte do menu podem ser removidos do estoque de forma simples.
Consultar Item: Os usuários podem buscar e visualizar detalhes de um item específico, como seu nome, preço, descrição e quantidade em estoque.

### Modificar Item

Permite a edição de informações de um item, como preço, nome, quantidade em estoque, mantendo os dados atualizados.

### Gerar Relatório de Itens com Baixo Estoque

O sistema gera automaticamente um relatório que lista os itens que estão com baixo estoque, de acordo com estoque mínimo fornecido pelo usuário.

### Gerar Relatório de Todos Itens

Um relatório completo de todos os itens disponíveis no estoque é gerado, fornecendo o nome, número identificador, preço e quantidade disponível no estoque.

### Gerar Relatório dos Itens Ordenados por Preço

Ao escolher esta opção, um relatório com os itens ordenados pelo preço será exibido ao usuário.

### Gerar Relatório das Últimas 50 Vendas

O sistema registra todas as vendas realizadas e permite a geração de um relatório das últimas 50 vendas, incluindo detalhes como data, itens vendidos e valor total.

## Instalação

Para instalar o Buteco do Geraldo, siga estas etapas:

### 1. Clone o repositório do GitHub:

```bash
git clone https://github.com/kistgab/project-1-edp.git
```

ou

```bash
git clone git@github.com:kistgab/project-1-edp.git
```

### 2. Navegue até o diretório do projeto:

```bash
cd buteco-do-geraldo
```

### 3. Execute o arquivo main.c

Para executar o arquivo você precisa de uma IDE ou um Editor de código compatível e que consiga executar arquivos da linguagem C

## Uso

Após a instalação, o Buteco do Geraldo estará disponível para uso. Para acessar as funcionalidades do sistema, selecione a opção desejada no menu principal.

## Documentação

### Adicionar Item

A funcionalidade Adicionar Item permite que os usuários adicionem novos itens ao estoque do boteco. Para isso, é necessário informar os seguintes dados:

- Nome: o nome do item.
- Quantidade inicial: a quantidade inicial do item em estoque.
  Preço de venda: o preço de venda do item.

Após informar, o sistema gera automaticamente as seguintes informações:

- Data de entrada: a data em que o item foi inserido no estoque.
- Número identificador: um número único e sequencial que identifica o item no sistema.

### Modificar Item

A funcionalidade Modificar Item permite que os usuários modifiquem informações de um item já existente no estoque.

Para isso, é necessário informar o número identificador do item que deseja modificar.

#### Erros

Os seguintes erros podem ocorrer ao modificar um item:

- Item não encontrado: o sistema não permitirá a modificação de um item que não existe no estoque.

### Remover Item

A funcionalidade Remover Item permite que os usuários removam itens do estoque.

Para isso, é necessário informar o número identificador do item que deseja remover.

#### Erros

Os seguintes erros podem ocorrer ao remover um item:

- Item não encontrado: o sistema não permitirá a remoção de um item que não existe no estoque.
- Item com estoque: o sistema não permitirá a remoção de um item que ainda possui estoque.

### Consultar Item

A funcionalidade Consultar Item permite que os usuários consultem informações de um item específico do estoque.

Para isso, é necessário informar o número identificador do item que deseja consultar.

#### Erros

- Item não encontrado: o sistema não permitirá a remoção de um item que não existe no estoque.

### Realizar Venda

A funcionalidade Realizar Venda permite que os usuários vendam itens do estoque do boteco.

Para isso, é necessário informar o número identificador do item e a quantidade vendida.

#### Erros

Os seguintes erros podem ocorrer ao realizar uma venda:

- Item não encontrado: o sistema não permitirá a venda de um item que não existe no estoque.
- Item sem estoque: o sistema não permitirá a venda de um item que não possui estoque suficiente.

### Gerar Relatório de Todos Itens

A funcionalidade Gerar Relatório de Todos Itens permite que os usuários gerem um relatório que lista todos os itens disponíveis no estoque.

### Gerar Relatório de Itens com Baixo Estoque

A funcionalidade Gerar Relatório de Itens com Baixo Estoque permite que os usuários gerem um relatório que lista os itens que estão com baixo estoque, de acordo com um estoque mínimo fornecido pelo usuário.

### Gerar Relatório de Itens em Ordem de Preço

A funcionalidade Gerar Relatório de Itens em Ordem de Preço permite que os usuários gerem um relatório que lista os itens em ordem decrescente de preço.

### Gerar Relatório das Últimas 50 Vendas

A funcionalidade Gerar Relatório das Últimas 50 Vendas permite que os usuários gerem um relatório que lista as últimas 50 vendas realizadas

## Contribuições

Contribuições são bem-vindas. Para contribuir com o projeto, envie uma solicitação de pull request para o repositório do GitHub.

## Fluxograma

[Acesse o fluxograma clicando aqui](https://www.figma.com/file/IHKh3BbkJikoSw8IvXPA8S/Welcome-to-FigJam?type=whiteboard&node-id=0%3A1&t=4obZH8GRmHqVXJm1-1)

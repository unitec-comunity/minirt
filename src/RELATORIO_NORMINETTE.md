# Relatório de normalização — miniRT/src

Data: 29/10/2026

## Escopo

Foram verificados e normalizados todos os 34 ficheiros `*.c` existentes em
`src` e respetivos subdiretórios. Conforme solicitado posteriormente, o
ficheiro `../includes/minirt.h` não foi alterado.

## Correções aplicadas

- Adicionados cabeçalhos padrão 42 aos ficheiros de código que não os tinham.
- Corrigidas tabulações, alinhamento, espaços em excesso e linhas vazias
  indevidas.
- Divididas funções que ultrapassavam os limites da Norma, sem alterar a
  lógica de interseção, cilindros ou renderização.
- A renderização por pixel passou a usar auxiliares locais para manter os
  limites de variáveis e de linhas por função.

Não foi criado nenhum novo ficheiro fonte, pelo que não foi necessária
nenhuma alteração ao `Makefile` nem ao cabeçalho público.

## Validação final

Comandos executados a partir de `src`:

```sh
norminette .
cc -Wall -Wextra -Werror -std=gnu17 \
  -I../includes -I../depemdences/minilibx-linux \
  -fsyntax-only $(rg --files -g '*.c' | sort)
```

Resultado: os 34 ficheiros C reportaram `OK` pela Norminette e a validação
sintática terminou sem avisos nem erros.

Não foi efetuada a ligação final do executável porque o diretório-pai do
projeto está montado como somente-leitura neste ambiente; foram removidos os
ficheiros `.o` temporários criados durante a tentativa de compilação.

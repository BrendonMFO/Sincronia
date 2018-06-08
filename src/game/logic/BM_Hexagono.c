#include "BM_Hexagono.h"
#include "BM_Campo.h"
#include "BM_Allegro_eventos_mouse.h"
#include "BM_Allegro.h"
#include "BM_Allegro_janela.h"
#include "BM_Recursos.h"
#include "BM_Elemento.h"
#include "BM_Recursos_Animacao.h"
#include "BM_Player.h"
#include "BM_Oponente.h"
#include <stdarg.h>

//==========================================================================
// Grafo de sincronia entre os elementos
//==========================================================================
const int BM_Sincronia[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                                {0, 1, -2, 2, -1, -1, 1},
                                {0, -2, 1, -1, 2, 1, -1},
                                {0, 2, -1, 1, -2, -1, 1},
                                {0, -1, 2, -2, 1, 1, -1},
                                {0, 1, 2, -1, -1, 1, -2},
                                {0, 1, -1, 2, -1, -2, 1}};
const int BM_Vantagem[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                               {0, 1, 0, 0, 0, 0, 0},
                               {0, 1, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 1},
                               {0, 0, 0, 1, 0, 0, 0},
                               {0, 0, 0, 0, 1, 0, 0},
                               {0, 0, 0, 0, 0, 1, 0}};

//==========================================================================
// Prototipos
//==========================================================================
void BM_Hexagono_adicionar_listener_mouse(BM_HEXAGONO *_alvo, int _acao);
void BM_Hexagono_adicionar_animacao(BM_HEXAGONO *_alvo);

//==========================================================================
// Criar Hexagono
//==========================================================================
BM_HEXAGONO BM_Hexagono_criar(int _id, int _estado, int _elemento)
{
    BM_HEXAGONO temp = {_id, _estado, _elemento, 0, HEXAGONO_NORMAL};
    return temp;
}

//==========================================================================
// Alterar estado e elemento do hexagono
//==========================================================================
void BM_Hexagono_alterar(int _hexagono_id, int _estado, int _elemento)
{
    BM_Campo *campo = BM_Campo_getCampo();
    campo->hexagonos[_hexagono_id].estado = _estado;
    campo->hexagonos[_hexagono_id].elemento = _elemento;
}

//==========================================================================
// Dominar territorio
//==========================================================================
int BM_Hexagono_batalha(int _alvo, int _atacante, int _playerAtaque, int _playerDefesa)
{
    int resultadoAtaque = 0, resultadoDefesa = 0;
    BM_Campo *campo = BM_Campo_getCampo();
    BM_HEXAGONO *hexagonoAtaque, *hexagonoDefesa;

    //======================================================================
    // Definir os hexagonos de ataque e defesa
    //======================================================================
    hexagonoAtaque = &campo->hexagonos[_atacante];
    hexagonoDefesa = &campo->hexagonos[_alvo];
    //======================================================================

    //======================================================================
    // Adicionar animações de batalha nos hexagonos
    //======================================================================
    BM_Hexagono_adicionar_animacao(hexagonoAtaque);
    BM_Hexagono_adicionar_animacao(hexagonoDefesa);
    //======================================================================

    //======================================================================
    // Setar hexagonos visiveis
    //======================================================================
    hexagonoAtaque->visivel = 1;
    hexagonoDefesa->visivel = 1;
    //======================================================================

    //======================================================================
    // Verificar se ha alguma superioridade de sincronia entre os hexagonos
    //======================================================================
    if (BM_Vantagem[hexagonoAtaque->elemento][hexagonoDefesa->elemento] == 1)
        resultadoAtaque += 4;
    else if (BM_Vantagem[hexagonoDefesa->elemento][hexagonoAtaque->elemento] == 1)
        resultadoDefesa += 4;

    //======================================================================
    // Calcular poder das sincronias
    //======================================================================
    resultadoAtaque += BM_Hexagono_calcular_sincronia(*hexagonoAtaque, _playerAtaque);
    resultadoDefesa += BM_Hexagono_calcular_sincronia(*hexagonoDefesa, _playerDefesa);

    //======================================================================
    // Determinar resultado
    //======================================================================
    if ((hexagonoAtaque->elemento != 0 && hexagonoDefesa->elemento == 0) || (resultadoAtaque > resultadoDefesa))
        return VITORIA_ATAQUE;
    if ((hexagonoDefesa->elemento != 0 && hexagonoAtaque->elemento == 0) || (resultadoDefesa > resultadoAtaque))
        return VITORIA_DEFESA;

    return EMPATE;
}

//==========================================================================
// Marcar alvos
//==========================================================================
int BM_Hexagono_marcar_alvos(int _centro, int _acao)
{
    BM_Campo *campo = BM_Campo_getCampo();
    BM_HEXAGONO hexagono = campo->hexagonos[_centro], *aux;
    int i, contador = 0;
    for (i = 0; i < 6; i++)
    {
        if (hexagono.conexoes[i] != -1)
        {
            aux = &campo->hexagonos[hexagono.conexoes[i]];
            if (aux->estado == ADVERSARIO)
            {
                BM_Hexagono_adicionar_listener_mouse(aux, _acao);
                aux->alvo = _acao;
                contador++;
            }
        }
    }
    return contador;
}

//==========================================================================
// Marcar sincronia entre os hexagonos
//==========================================================================
void BM_Hexagono_marcar_sincronia(int _player)
{
    BM_Campo *campo = BM_Campo_getCampo();
    BM_HEXAGONO hexagono, *aux;
    if (_player == JOGADOR)
        hexagono = campo->hexagonos[BM_Player_getJogador()->hexagonoAtual];
    else
        hexagono = campo->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual];
    int i;
    for (i = 0; i < 6; i++)
    {
        if (hexagono.conexoes[i] != -1)
        {
            aux = &campo->hexagonos[hexagono.conexoes[i]];
            if (aux->estado == _player)
            {
                switch (BM_Sincronia[hexagono.elemento][aux->elemento])
                {
                case 2:
                    aux->alvo = HEXAGONO_SINCRONIA;
                    break;
                case 1:
                    aux->alvo = HEXAGONO_BAIXA_SINCRONIA;
                    break;
                case -1:
                    aux->alvo = HEXAGONO_BAIXA_ANTI_SINCRONIA;
                    break;
                case -2:
                    aux->alvo = HEXAGONO_ANTI_SINCRONIA;
                }
            }
        }
    }
}

//==========================================================================
// Desmarcar sincronia entre os hexagonos
//==========================================================================
void BM_Hexagono_desmarcar_sincronia(int _player)
{
    BM_Campo *campo = BM_Campo_getCampo();
    BM_HEXAGONO hexagono, *aux;
    if (_player == JOGADOR)
        hexagono = campo->hexagonos[BM_Player_getJogador()->hexagonoAtual];
    else
        hexagono = campo->hexagonos[BM_Player_getOpponentPlayer()->hexagonoAtual];
    int i;
    for (i = 0; i < 6; i++)
    {
        if (hexagono.conexoes[i] != -1)
        {
            aux = &campo->hexagonos[hexagono.conexoes[i]];
            if (aux->estado == _player)
            {
                aux->alvo = HEXAGONO_NORMAL;
            }
        }
    }
}

//==========================================================================
// Adicionar/Remover listener de eventos do mouse no hexagono selecionado
//==========================================================================
void BM_Hexagono_adicionar_listener_mouse(BM_HEXAGONO *_alvo, int _acao)
{
    int finalX, finalY, *id;
    finalX = _alvo->posicaoX + SPRITES(BM_IMG_HEXAGONO_ALVO)->ajusteW;
    finalY = _alvo->posicaoY + SPRITES(BM_IMG_HEXAGONO_ALVO)->ajusteH;
    switch (_acao)
    {
    case HEXAGONO_ALVO:
        id = (int *)malloc(1 * sizeof(int));
        *id = _alvo->id;
        BM_Eventos_Mouse_adicionar(NULL, _alvo->posicaoX, _alvo->posicaoY, finalX, finalY, id);
        break;
    case HEXAGONO_NORMAL:
        BM_Eventos_Mouse_remover(_alvo->posicaoX, _alvo->posicaoY, finalX, finalY);
        break;
    }
}

//==========================================================================
// Calcular vinculo
//==========================================================================
int BM_Hexagono_calcular_sincronia(BM_HEXAGONO _alvo, int _player)
{
    int resultado = 0, i;
    BM_Campo *campo = BM_Campo_getCampo();
    BM_HEXAGONO aux;
    for (i = 0; i < 6; i++)
    {
        if (_alvo.conexoes[i] != -1)
        {
            aux = campo->hexagonos[_alvo.conexoes[i]];
            if (aux.estado == _player)
                resultado += BM_Sincronia[_alvo.elemento][aux.elemento];
        }
    }
    return resultado;
}

//==========================================================================
// Adicionar animações de batalha
//==========================================================================
void BM_Hexagono_adicionar_animacao(BM_HEXAGONO *_alvo)
{
    switch (_alvo->elemento)
    {
    case LUZ:
        BM_Animacao_adicionar(SPRITES(BM_ANI_LUZ), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_AJUSTE_YH(20)), 0.5);
        break;
    case TREVAS:
        BM_Animacao_adicionar(SPRITES(BM_ANI_TREVAS), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_AJUSTE_YH(20)), 0.5);
        break;
    case FOGO:
        BM_Animacao_adicionar(SPRITES(BM_ANI_FOGO), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_AJUSTE_YH(20)), 0.5);
        break;
    case AGUA:
        BM_Animacao_adicionar(SPRITES(BM_ANI_AGUA), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_AJUSTE_YH(20)), 0.5);
        break;
    case TERRA:
        BM_Animacao_adicionar(SPRITES(BM_ANI_TERRA), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_AJUSTE_YH(20)), 0.5);
        break;
    case AR:
        BM_Animacao_adicionar(SPRITES(BM_ANI_AR), 250, 250, (_alvo->posicaoX), (_alvo->posicaoY - BM_AJUSTE_YH(20)), 0.5);
    }
}

//==========================================================================
// Click hexagono
//==========================================================================
BM_HEXAGONO *BM_Hexagono_click(int _mouseX, int _mouseY)
{
    BM_Campo *campo = BM_Campo_getCampo();
    BM_HEXAGONO *hexagono = NULL;
    int i, largura, altura;
    for (i = 0; i < campo->quantidade; i++)
    {
        hexagono = &campo->hexagonos[i];
        largura = BM_AJUSTE_XW(hexagono->posicaoX) + SPRITES(BM_IMG_HEXAGONO)->ajusteW;
        altura = BM_AJUSTE_YH(hexagono->posicaoY) + SPRITES(BM_IMG_HEXAGONO)->ajusteH;
        if (_mouseX >= BM_AJUSTE_XW(hexagono->posicaoX) && _mouseX <= largura &&
            _mouseY >= BM_AJUSTE_YH(hexagono->posicaoY) && _mouseY <= altura)
        {
            break;
        }
    }
    if (i != campo->quantidade)
        return hexagono;
    return NULL;
}
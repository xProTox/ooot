#include <algorithm>
#include "players.h"
#include "../controller/controllers.h"
#include "../options.h"

#include "z64.h";
#include "padmgr.h"

extern PadMgr gPadMgr;

using namespace oot::hid;

Players g_players;


Players& Players::get()
{
	return g_players;
}

void Players::Update()
{
	g_players.update();
}

int Players::mouse_x()
{
	int res = 0;

	for(auto it : g_players[0].controllers())
	{
		if(it.get()->mouse_x != 0)
		{
			return it.get()->mouse_x;
		}
	}

	return res;
}

int Players::mouse_y()
{
	int res = 0;

	for(auto it : g_players[0].controllers())
	{
		if(it.get()->mouse_y != 0)
		{
			return it.get()->mouse_y;
		}
	}

	return res;
}

const Controller* Players::GetController()
{
	if (g_players[0].controllers().size() == 0)
		return nullptr;
	return g_players[0].controllers()[0].get();
}



void Players::update()
{
    memset(&gPadMgr.ctrlrIsConnected[0], 0, sizeof(gPadMgr.ctrlrIsConnected));

	int i = 0;
	for (auto& player : m_players)
	{
		player.update();

		gPadMgr.inputs[i].cur.button  = player.controller().state().button;
		gPadMgr.inputs[i].cur.stick_x = player.controller().state().stick_x;
		gPadMgr.inputs[i].cur.stick_y = player.controller().state().stick_y;

		gPadMgr.inputs[i].cur.mouse_x = player.controller().state().mouse_x;
		gPadMgr.inputs[i].cur.mouse_y = player.controller().state().mouse_y;

		gPadMgr.ctrlrIsConnected[i] = true;
		i++;
	}

	gPadMgr.nControllers = i;
}



void Players::attach(const std::shared_ptr<Controller>& controller, const u8 playerId)
{
	if (playerId == MAX_PLAYERS)
		m_players[m_size++].attach(controller);
	else
	{
		m_players[playerId].attach(controller);
		m_size = std::max((u64)playerId + 1, m_size);
	}
}
/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef VOYEUR_EVENTS_H
#define VOYEUR_EVENTS_H

#include "common/scummsys.h"
#include "common/list.h"
#include "graphics/surface.h"
#include "voyeur/files.h"

namespace Voyeur {

class VoyeurEngine;
class EventsManager;
class CMapResource;

#define GAME_FRAME_RATE 50
#define GAME_FRAME_TIME (1000 / GAME_FRAME_RATE)

typedef void (EventsManager::*EventMethodPtr)();
 
class IntNode {
public:
	EventMethodPtr _intFunc;
	uint16 _curTime;
	uint16 _timeReset;
	uint32 _flags;
public:
	IntNode();
	IntNode(uint16 curTime, uint16 timeReset, uint16 flags);
};

class IntData {
public:
	bool _flipWait;
	int _flashTimer;
	int _flashStep;
	int field26;
	bool _hasPalette;
	bool _skipFading;
	int _palStartIndex;
	int _palEndIndex;
	byte *_palette;
public:
	IntData();
};

class EventsManager {
private:
	VoyeurEngine *_vm;
	uint32 _priorFrameTime;
	bool _counterFlag;
	uint32 _gameCounter;
	uint32 _recordBlinkCounter;	// Original field was called _joe :)
	int _mouseButton;
	Common::List<IntNode *> _intNodes;
	Common::Point _mousePos;
	bool _cursorBlinked;

	void mainVoyeurIntFunc();
private:
	void checkForNextFrameCounter();
	void voyeurTimer();
	void videoTimer();
	void vDoFadeInt();
	void vDoCycleInt();
	void fadeIntFunc();
	void deleteIntNode(IntNode *node);

	/**
	 * Debugger support method to show the mouse position
	 */
	void showMousePosition();
public:
	IntData _gameData;
	IntData &_intPtr;
	IntNode _fadeIntNode;
	IntNode _fade2IntNode;
	IntNode _cycleIntNode;
	IntNode _evIntNode;
	IntNode _mainIntNode;
	int _cycleStatus;
	int _fadeFirstCol, _fadeLastCol;
	int _fadeCount;
	int _fadeStatus;

	bool _leftClick, _rightClick;
	bool _mouseClicked;
	bool _mouseUnk;
	bool _newMouseClicked;
	bool _newLeftClick, _newRightClick;
	bool _newMouseUnk;

	int _videoDead;
	int _cycleTime[4];
	byte *_cycleNext[4];
	VInitCycleResource *_cyclePtr;
public:
	EventsManager();
	void setVm(VoyeurEngine *vm) { _vm = vm; }

	void resetMouse();
	void setMousePos(const Common::Point &p) { _mousePos = p; }
	void startMainClockInt();
	void sWaitFlip();
	void vInitColor();

	void delay(int cycles);
	void delayClick(int cycles);
	void pollEvents();
	void startFade(CMapResource *cMap);
	void addIntNode(IntNode *node);
	void addFadeInt();

	void setCursor(PictureResource *pic);
	void setCursor(byte *cursorData, int width, int height);
	void setCursorColor(int idx, int mode);
	void showCursor();
	void hideCursor();
	Common::Point getMousePos() { return _mousePos; }
	uint32 getGameCounter() const { return _gameCounter; }
	void getMouseInfo();
	void startCursorBlink();
	void incrementTime(int amt);

	void stopEvidDim();

	Common::String getEvidString(int eventIndex);
};

} // End of namespace Voyeur

#endif /* VOYEUR_EVENTS_H */
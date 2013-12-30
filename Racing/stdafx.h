// stdafx.h : fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <memory>
#include <thread>

#include <sstream>

#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <Box2D/Box2D.h>

typedef unsigned int uint;

#include "GConst.h"
#include "Utils.h"
#include "GameObject.h"

inline void dassert(bool b)
{
#ifdef _DEBUG
	assert(b);
#endif // _DEBUG
}


// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

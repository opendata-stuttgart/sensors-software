#ifndef intl_h
#define intl_h

#if defined(INTL_BG)
#include "intl_bg.h"
#elif defined(INTL_CZ)
#include "intl_cz.h"
#elif defined(INTL_DE)
#include "intl_de.h"
#elif defined(INTL_DK)
#include "intl_dk.h"
#elif defined(INTL_EN)
#include "intl_en.h"
#elif defined(INTL_ES)
#include "intl_es.h"
#elif defined(INTL_FR)
#include "intl_fr.h"
#elif defined(INTL_HU)
#include "intl_hu.h"
#elif defined(INTL_IT)
#include "intl_it.h"
#elif defined(INTL_LU)
#include "intl_lu.h"
#elif defined(INTL_NL)
#include "intl_nl.h"
#elif defined(INTL_PL)
#include "intl_pl.h"
#elif defined(INTL_PT)
#include "intl_pt.h"
#elif defined(INTL_RS)
#include "intl_rs.h"
#elif defined(INTL_RU)
#include "intl_ru.h"
#elif defined(INTL_SE)
#include "intl_se.h"
#elif defined(INTL_TR)
#include "intl_tr.h"
#elif defined(INTL_UA)
#include "intl_ua.h"
#else
#warning No language defined
#include "intl_en.h"
#endif

#endif

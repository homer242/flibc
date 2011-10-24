#ifndef _FLC_MATH_H_
#define _FLC_MATH_H_

/*! \def min(x, y)
 */
#define min(x, y)                                   \
        ({                                          \
                typeof(x) _x = (x);                 \
                typeof(y) _y = (y);                 \
                _x < _y ? _x : _y;                  \
        })

/*! \def max(x, y)
 */
#define max(x, y)                                   \
        ({                                          \
                typeof(x) _x = (x);                 \
                typeof(y) _y = (y);                 \
                _x > _y ? _x : _y;                  \
        })

#endif

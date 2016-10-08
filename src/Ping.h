#ifndef _Ping_H
#define _Ping_H

#define PING_TIMEOUT_INTERVAL 20000

#ifdef __cplusplus
extern "C" {
#endif

long getEchoDuration();

long microsecondsToCentimeters(long);

long measureDistanceInCentimeters();

#ifdef __cplusplus
}
#endif

#endif

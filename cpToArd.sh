cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/croutine.c /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/croutine.c
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/croutine.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/croutine.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/event_groups.c /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/event_groups.c
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/event_groups.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/event_groups.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/list.c /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/list.c
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/list.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/list.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/projdefs.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/projdefs.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/queue.c /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/queue.c
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/queue.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/queue.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/semphr.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/semphr.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/StackMacros.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/StackMacros.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/task.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/task.h
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/tasks.c /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/tasks.c
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/timers.c /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/timers.c
cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/timers.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/timers.h
# cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/portable.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/portable.h

find /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/*.c -print0 | xargs -0 sed -i "" 's/#include "FreeRTOS\.h"/#include "Arduino_FreeRTOS\.h"/g' 
find /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/*.h -print0 | xargs -0 sed -i "" 's/INC_FREERTOS_H/INC_ARDUINO_FREERTOS_H/g' 

cp /Users/andrej/Downloads/FreeRTOS-Sim-master/Source/include/FreeRTOS.h /Users/andrej/Documents/Arduino/libraries/Arduino_FreeRTOS-master/src/FreeRTOS.h

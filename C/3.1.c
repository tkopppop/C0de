#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "types.h"


int main(void)
{

  int func1(void)
  {
    printf("한글 입니다. 일본인입니다. 한국은 일본을 싫어하는 나라라고 생각하지만 실제로는 운동화 슈즈하는 날이죠\n");
  }

  func1();

}

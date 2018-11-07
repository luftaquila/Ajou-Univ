#include <stdio.h>
void convertLength(int *unit, double *value);
void convertVelocity(int *unit, double *value);
void convertTime(int *unit, double *value);
void convertUnit(int *input, int *unit, double *value);

int main()
{
  int input, unit;
  double value;

  convertUnit(&input, &unit, &value);
}

void convertLength(int *unit, double *value)
{
  printf("입력된 값 + 단위 : %lf", *value);
  switch(*unit)
  {
    case 1 :
      printf(" um\n");
      printf("%lf um\n%lf mm\n%lf cm\n%lf m\n%lf km\n",
        *value, *value * 0.001, *value * 0.0001, *value * 0.000001, *value * 0.000000001);
      break;

    case 2 :
      printf(" mm\n");
      printf("%lf um\n%lf mm\n%lf cm\n%lf m\n%lf km\n",
        *value * 1000, *value, *value * 0.1, *value * 0.001, *value * 0.000001);
      break;

    case 3 :
      printf(" cm\n");
      printf("%lf um\n%lf mm\n%lf cm\n%lf m\n%lf km\n",
        *value * 10000, *value * 10, *value, *value * 0.01, *value * 0.00001);
      break;

    case 4 :
      printf(" m\n");
      printf("%lf um\n%lf mm\n%lf cm\n%lf m\n%lf km\n",
        *value * 1000000, *value * 1000, *value * 100, *value, *value * 0.001);
      break;

    case 5 :
      printf(" km\n");
      printf("%lf um\n%lf mm\n%lf cm\n%lf m\n%lf km\n",
        *value * 1000000, *value * 1000, *value * 100, *value, *value * 0.001);
      break;

    default :
      printf("wrong input\n");
  }
}

void convertVelocity(int *unit, double *value)
{
  printf("입력된 값 + 단위 : %lf", *value);
  switch(*unit)
  {
    case 1 :
      printf(" m/s\n");
      printf("%lf m/s\n%lf m/h\n%lf km/s\n%lf km/h\n",
        *value, *value * 3600, *value * 0.001, *value * 3.6);
      break;

    case 2 :
      printf(" m/h\n");
      printf("%lf m/s\n%lf m/h\n%lf km/s\n%lf km/h\n",
        *value / 3600, *value, *value * 2.7777, *value * 0.001);
      break;

    case 3 :
      printf(" km/s\n");
      printf("%lf m/s\n%lf m/h\n%lf km/s\n%lf km/h\n",
        *value * 1000, *value * 3600000, *value, *value * 3600);
      break;

    case 4 :
      printf(" km/h\n");
      printf("%lf m/s\n%lf m/h\n%lf km/s\n%lf km/h\n",
        *value / 3.6, *value * 1000, *value / 3600, *value);
      break;

    default :
      printf("wrong input\n");
  }

}

void convertTime(int *unit, double *value)
{
  printf("입력된 값 + 단위 : %lf", *value);
  switch(*unit)
  {
    case 1 :
      printf(" s\n");
      printf("%lf s\n%lf m\n%lf h\n%lf day\n%lf week\n",
        *value, *value / 60, *value / 3600, *value / 3600 / 24, *value / 3600 / 24 / 7);
      break;

    case 2 :
      printf(" m\n");
      printf("%lf s\n%lf m\n%lf h\n%lf day\n%lf week\n",
        *value * 60, *value, *value / 60, *value / 60 / 24, *value / 60 / 24 / 7);
      break;

    case 3 :
      printf(" h\n");
      printf("%lf s\n%lf m\n%lf h\n%lf day\n%lf week\n",
        *value * 3600, *value * 60, *value, *value / 24, *value / 24 / 7);
      break;

    case 4 :
      printf(" day\n");
      printf("%lf s\n%lf m\n%lf h\n%lf day\n%lf week\n",
        *value * 3600 * 24, *value * 60 * 24, *value * 24, *value, *value / 7);
      break;

    case 5 :
      printf(" week\n");
      printf("%lf s\n%lf m\n%lf h\n%lf day\n%lf week\n",
        *value * 3600 * 24 * 7, *value * 60 * 24 * 7, *value * 24 * 7, *value * 7, *value);
      break;

    default :
      printf("wrong input\n");
  }
}

void convertUnit(int *input, int *unit, double *value)
{
  printf("길이변환(1), 속력변환(2), 시간변환(3) : ");
  scanf("%d", input);
  switch(*input)
  {
    case 1 :
      printf("um(1), mm(2), cm(3), m(4), km(5) 입력 단위 선택 : ");
      scanf("%d", unit);
      printf("변환할 값 : ");
      scanf("%lf", value);
      convertLength(unit, value);
      break;

    case 2 :
      printf("m/s(1), m/h(2), km/s(3), km/h(4) 입력 단위 선택 : ");
      scanf("%d", unit);
      printf("변환할 값 : ");
      scanf("%lf", value);
      convertVelocity(unit, value);
      break;

    case 3 :
      printf("s(1), m(2), h(3), day(4), week(5) 입력 단위 선택 : ");
      scanf("%d", unit);
      printf("변환할 값 : ");
      scanf("%lf", value);
      convertTime(unit, value);
      break;

    default :
      printf("wrong input\n");
      convertUnit(input, unit, value);
  }
}

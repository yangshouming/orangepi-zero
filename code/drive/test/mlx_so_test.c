/*******************************************************************************
 * @Copyright: 深圳和而泰家居在线网络科技有限公司(2020)
 * @Description: Description
 * @Author: Stream
 * @Version: V0.0.1
 * @Date: 2020-01-15 11:30:59
 * @LastEditors: Stream
 * @LastEditTime: 2020-06-29 10:59:25
 * @FilePath: \code\drive\test\mlx_so_test.c
 * @ChangeLog: ChangeLog
*******************************************************************************/

#include <stdio.h>
#include <sys/time.h>

#include "mlx.h"
#include <unistd.h>
//将编译好的 libmlx.so 放到 /usr/lib/
//以下是测试数据------------------------------------------------------------------------
static uint16_t mlx90640Frame_app[834]; //原始图像数据   APP测试数据
static float mlx90640To_app[768];       //计算后的图像数据		APP测试数据

static struct timeval start, end;
static int interval;

static unsigned long run_cnt;             //运行次数统计
static unsigned long get_source_data_cnt; //运行次数统计
static unsigned long get_calc_data_cnt;   //运行次数统计
static float get_source_data_percent;     //
static float get_calc_data_percent;       //
int error_image;

//计算百分比

static float get_data_correct_percent(int data_target, int data_source)
{
    float sdata_target = data_target;
    float sdata_source = data_source;
    return (sdata_target / sdata_source) * 100;
}

/******************************************************************************\
                             Functions definitions
\******************************************************************************/

int main(int argc, char **argv)
{
    int i;
    uint8_t rate = 0;
    float max_temp = 0;
    float min_temp = 100;

    //初始化
    mlx_init();

    //设置刷新率
    usleep(100 * 1000);
    mlx_set_refresh_rate(0X05); //刷新率 //0x01 – 1Hz //0x02 – 2Hz //0x03 – 4Hz //0x04 – 8Hz //0x05 – 16Hz //0x06 – 32Hz
    usleep(100 * 1000);
    mlx_get_refresh_rate(&rate);
    printf("mlx_get_refresh_rate 0x%x\n", rate);

    while (1)
    {

        gettimeofday(&start, NULL); //计时开始

        usleep(10 * 1000); //延时时间 帧率控制

        if (mlx_get_source_data(mlx90640Frame_app) == 0) //采集数据
        {
            get_source_data_cnt++;
        }

        if (mlx_get_calculate_data(mlx90640To_app, mlx90640Frame_app) == 0) //计算数据
        {
            get_calc_data_cnt++;

            //以下是测试------------------------------------------------------------------------------------------
            gettimeofday(&end, NULL);                                                         //计时结束
            interval = 1000000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec); //统计运行耗时
            printf("interval = %f  fps = %.1f \n", interval / 1000.0, 1000000.0 / interval);  //计算帧率

            int image_error = 0;

            max_temp = 0;
            min_temp = 1000;

            for (i = 0; i < 768;)
            {

                if (mlx90640To_app[i] > max_temp)
                {
                    max_temp = mlx90640To_app[i];
                }

                if (mlx90640To_app[i] < min_temp)
                {
                    min_temp = mlx90640To_app[i];
                }

                //if ((mlx90640To_app[i] < 15) | (mlx90640To_app[i] > 40))
                if ((mlx90640To_app[i] > 40))
                {
                    //异常数据打印，并退出
                    printf("\nhight 40 error i:%d run_cnt:%d\n", i, run_cnt);
                    printf("temp:%.1f \n", mlx90640To_app[i]);
                    image_error = 1;
                    // return -1;
                }
                else if (mlx90640To_app[i] < 15)
                {
                    printf("\nlow 15 error i:%d run_cnt:%d\n", i, run_cnt);
                    printf("temp:%.1f \n", mlx90640To_app[i]);
                    image_error = 1;
                }
                else
                {
                    //正常数据打印
                    printf("%.1f ", mlx90640To_app[i]);
                }

                i++;
                if ((i % 32) == 0)
                {
                    printf("\n");
                }
            }

            if (image_error == 0)
            {
                printf("image ok \n");
            }
            else
            {
                printf("image eroor \n");
                error_image++;
                printf("\n");
                for (i = 0; i < 834;)
                {
                    printf("%x ", mlx90640Frame_app[i]);
                    i++;
                    if ((i % 32) == 0)
                    {
                        printf("\n");
                    }
                }
                printf("\n");
                //  return -1;
            }
            printf("min_temp:%.1f,max_temp:%.1f,error_image:%d", min_temp, max_temp, error_image);
            printf("\n");
        }
        else
        {
            /* code */
            printf("mlx_get_calculate_data error \n");
        }

        run_cnt++;
        if (get_calc_data_cnt >= 57600) //成功率数据统计
        {
            get_source_data_percent = get_data_correct_percent(get_source_data_cnt, run_cnt);
            get_calc_data_percent = get_data_correct_percent(get_calc_data_cnt, run_cnt);
            printf("\nget_source\t%d\t%.1f\%\nget_calc_data\t%d\t%.1f\%\ntotal_run_cnt\t%d\n", get_source_data_cnt, get_source_data_percent, get_calc_data_cnt, get_calc_data_percent, run_cnt);
            break;
        }
    }
    printf("break exit\n");
    return 0;
}
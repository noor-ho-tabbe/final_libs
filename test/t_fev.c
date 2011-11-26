/*
 * =====================================================================================
 *
 *       Filename:  t_fev.c
 *
 *    Description:  test fev
 *
 *        Version:  1.0
 *        Created:  11/26/2011 12:29:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  finaldie
 *        Company:  
 *
 * =====================================================================================
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "tu_inc.h"
#include "inc.h"
#include "fev.h"
#include "net_core.h"

typedef struct {
    fev_state* fev;
    int fd;
}test_arg;

void test_fev_read(fev_state* fev, int fd, int mask, void* arg)
{
    test_arg* _arg = (test_arg*)arg;

    FTU_ASSERT_EXPRESS(_arg->fev==fev);
    FTU_ASSERT_EQUAL_INT(fd, _arg->fd);
}

void test_fev()
{
    fev_state* fev = fev_create(1024);
    FTU_ASSERT_EXPRESS(fev!=NULL);

    int fd = net_create_listen(NULL, 17758, 100, 0);
    FTU_ASSERT_GREATER_THAN_INT(0, fd);

    int ret = fev_reg_event(NULL, fd, 0, NULL, NULL, NULL);
    FTU_ASSERT_EQUAL_INT(-1, ret);

    ret = fev_reg_event(fev, fd, FEV_NIL, NULL, NULL, NULL);
    FTU_ASSERT_EQUAL_INT(-2, ret);

    ret = fev_reg_event(fev, fd, FEV_NIL | FEV_ERROR, NULL, NULL, NULL);
    FTU_ASSERT_EQUAL_INT(-2, ret);

    // test for add event before register event
    ret = fev_add_event(fev, fd, FEV_READ);
    FTU_ASSERT_EQUAL_INT(-2, ret);

    ret = fev_reg_event(fev, fd, FEV_READ, NULL, NULL, NULL);
    FTU_ASSERT_EQUAL_INT(0, ret);

    // test for duplicate register event
    ret = fev_reg_event(fev, fd, FEV_WRITE, NULL, NULL, NULL);
    FTU_ASSERT_EQUAL_INT(-3, ret);

    ret = fev_add_event(NULL, fd, 0);
    FTU_ASSERT_EQUAL_INT(-1, ret);

    ret = fev_add_event(fev, fd, FEV_NIL);
    FTU_ASSERT_EQUAL_INT(0, ret);

    ret = fev_add_event(fev, fd, FEV_ERROR);
    FTU_ASSERT_EQUAL_INT(0, ret);

    ret = fev_add_event(fev, fd, FEV_READ);
    FTU_ASSERT_EQUAL_INT(0, ret);

    ret = fev_add_event(fev, fd, FEV_WRITE);
    FTU_ASSERT_EQUAL_INT(0, ret);

    ret = fev_del_event(NULL, fd, FEV_WRITE);
    FTU_ASSERT_EQUAL_INT(-1, ret);

    ret = fev_del_event(fev, fd, FEV_NIL);
    FTU_ASSERT_EQUAL_INT(0, ret);

    // by now there are two status in fd:FEV_READ & FEV_WRITE
    ret = fev_del_event(fev, fd, FEV_READ);
    FTU_ASSERT_EQUAL_INT(0, ret);

    ret = fev_del_event(fev, fd, FEV_WRITE);
    FTU_ASSERT_EQUAL_INT(0, ret);

    // now the fd has deleted from fev_state
    // so we can retest add event , lookup whether or not sucess
    ret = fev_add_event(fev, fd, FEV_READ);
    FTU_ASSERT_EQUAL_INT(-2, ret);

    fev_destroy(fev);
    close(fd);
}
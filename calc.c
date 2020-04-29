#include<stdio.h>
#include<unistd.h>
#include<string.h>

//still in process

size_t ft_strlen(char *s)
{
    return(*s != '\0' ? 1 + ft_strlen(s + 1) : 0);
}

char *skobki(char *s, char c)
{
    if (*s == '(')
    {
        if (*(s + 1) == '+' || *(s + 1) == '*' ||
                *(s + 1) == '/' || *(s + 1) == '.' ||
                *(s + 1) == ')')
            return(NULL);
        if ((s = skobki(s + 1, ')')) == NULL)
            return(NULL);
    }
    else if (*s == '\0')
    {
        if (c != 0)
            return(NULL);
        return("correct");
    }
    else if (c == ')' && *s == ')')
        return(s + 1);
    else if (*s == ')' && c == 0)
        return(NULL);
    else
        return(skobki(s + 1, c));
    return(skobki(s, c));
}

void ft_zachem_probely_a(char *s)
{
    if (*s == '\0')
        return ;
    *s = *(s + 1);
    ft_zachem_probely_a(s + 1);
}


int ft_checksign(char *s)
{
    if (!*s )
        return(1);
    if (*s == '+' || *s == '*' || *s == '/' || *s == '-')
    {
        if ((*(s + 1) >= '0' && *(s + 1) <= '9') || *(s + 1) == '(')
            return(ft_checksign(s + 1));
        if (*(s + 1) == '-' && (*(s + 2) >= '0' && *(s + 2) <= '9'))
            return(ft_checksign(s + 2));
        return(0);
    }
    if ((*s >= '0' && *s <= '9') || *s == '(' || *s == ')')
        return(ft_checksign(s + 1));
//    if (*s == '.' && !(*(s + 1) >= '0' && *(s + 1) <= '9') &&
//            !(*(s - 1) >= '0' && *(s - 1) <= '9'))
    return(0);
    return(0);
}

int check(char *s)
{
    if (*s == '\0' || *s == '\n')
    {
        if (*s == '\n')
            *s = '\0';
        return(1);
    }
    if (*s == ' ')
    {
        ft_zachem_probely_a(s);
        return(check(s));
    }
    if(*s >= '0' && *s <= '9')
        return(check(s + 1));
    if (*s == '.' ||
            *s == '+' || *s == '-' || *s == '*' ||
            *s == '/' || *s == ' ' || *s == '(' ||
            *s == ')')
        return(check(s + 1));
    return(0);
}

size_t ft_strnum(char *s)
{
    if (!*s)
        return(0);
    if (*s == '-' && *(s + 1) == '-')
        return(2 + ft_strnum(s + 2));
    if (*s == '(' || *s == ')')
        return(1 + ft_strnum(s + 1));
    if ((*s == '+' || *s == '*' || *s == '/') &&
            (*(s + 1) == '-' || *(s + 1) == '('))
        return(1 + ft_strnum(s + 1));
    return(*s == '+' || *s == '*' || *s == '/' || *s == '-' ?
           2 + ft_strnum(s + 1) : ft_strnum(s + 1));
}

size_t ft_strlong(char *s)
{
    if (*s == '+' || *s == '*' || *s == '/'
            || *s == '-' || *s == '(' || *s == ')')
        return(1);
    return((*s >= '0' && *s <= '9') ?
           (*(s + 1) >= '0' && *(s + 1) <= '9') ?
           1 + ft_strlong(s + 1) : 1 : 0);
}

void ft_null(char *s, int i)
{
    *s = '\0';
    if (i == 0)
        return ;
    ft_null(s + 1, --i);
}

void free_str(char **buf)
{
    free(*buf);
    *buf = NULL;
    if (*(buf + 1) == NULL)
        return ;
    free_str(++*buf);
}
char **ft_free(char **buf)
{
    free_str(buf);
    free(buf);
    buf = NULL;
}

void ft_rew(char *buf, char *s, size_t n)
{
    *buf = s[n];
    if (n == 0)
        return ;
    ft_rew(buf + 1, s, --n);
}

void split_str(char **buf, char *s, size_t k, size_t i)
{
    size_t n;

    if (i == k)
        return(buf);
    n = ft_strlong(s);
    if (!(buf[i] = malloc(sizeof(char) * (n + 1))))
    {
        buf[i] = NULL;
        ft_free(buf);
        buf = NULL;
        return ;
    }
    ft_null(buf[i], n);
    buf[i][n] == '\0';
    if (*s == '-' && *(s + 1) == '-')
    {
        buf[i][0] = '+';
        s += 1;
    }
    else
        ft_rew(buf[i], s, n - 1);
    split_str(buf, s + n, k, ++i);
}

char **str_split(char *s)
{
    char **buf;
    size_t k = 1;

    if (*s == '-')
        k += 1 + ft_strnum(s + 1);
    else
        k += ft_strnum(s);
    if (!(buf = malloc(sizeof(char *) * (k + 1))))
        return(NULL);
    buf[k] = NULL;
    split_str(buf, s, k, 0);
    return(buf);
}

void ft_putstr(char *s)
{
    write(1,s,ft_strlen(s));
    write(1,"\n",1);
}

void revstr(char *s, size_t i)
{
    write(1,&s[--i],1);
    if (i == 0)
    {
        write(1,"\n",1);
        return ;
    }
    revstr(s, i);
}

void rerew(char *s, char *s2)
{
    if (!(*s2))
    {
        if (*s != '-')
            *s = '\0';
        return ;
    }
    *s = *s2;
    rerew(s + 1, s2 + 1);
}

size_t ft_naher_skobki(char **buf)
{
    if (**buf == '(')
    {
        *buf++;
        return(1 + ft_naher_skobki(buf));
    }
    return(0);
}

void sumnum(char *s)
{
    *s -= 10;
    if (*(s + 1) == '\0')
        *(s + 1) = '0';
    *(s + 1) += 1;
    if (*(s + 1) <= '9')
        return ;
    sumnum(s + 1);
}

void ft_sum(char *s, char *c)
{
    if (*c == '\0')
        return ;
    if (*s == '\0')
        *s = '0';
    *s = *s + (*c - 48);
    if (*s > '9')
        sumnum(s);
    ft_sum(s + 1, c + 1);
}

void ft_next_zero(char *s)
{
    if (*s == '0')
    {
        *s = '9';
        ft_next_zero(s + 1);
    }
    else
        *s = *s - 1;
    if (*s == '0' && *(s + 1) == '\0')
        *s = '\0';
}

void change(char *s, char *c)
{
    char i;

    if (!(*c))
        return ;
    i = *s;
    *s = *c;
    *c = i;
    change(s + 1, c + 1);
}

void ft_raz(char *s, char *c, size_t i)
{
    char *str;

    if (c[i] == '-')
        i--;
    if (s[i] < c[i])
    {
        if (s[i + 1] == '\0')
        {
            change(s,c);
            s[ft_strlen(s)] = '-';
            ft_raz(s, c, ft_strlen(c) - 1);
            return ;
        }
        else
        {
            s[i] = s[i] + 10 - (c[i] - '0');
            if (s[i + 1] != '0')
                s[i + 1] -= 1;
            else
                ft_next_zero(s += i + 1);
            if (s[i + 1] == '0' && s[i + 2] == '\0')
                s[i + 1] = '\0';
            if (s[i + 1] == '0' && s[i + 2] == '-')
            {
                s[i + 1] = '-';
                s[i + 2] = '\0';
            }
        }
    }
    else
    {
        s[i] = s[i] - c[i] + '0';
        if (s[i] == '0' && s[i + 1] == '\0')
            s[i] = '\0';
    }
 //   c[i] = '\0';
    if (i == 0)
    {
        if (s[0] == '\0')
            s[0] = '0';
        return ;
    }
    ft_raz(s, c, i - 1);
}

int chack_nullis(char *s)
{
    return(*s == '\0' || *s == '-' ? 0 : *s == '0' ? chack_nullis(s + 1) : 1);
}

void ft_itoa(char *s, int k)
{
    if (k == 0)
    {
        *s = '\0';
        return ;
    }
    *s = k % 10 + '0';
    ft_itoa(s + 1, k / 10);
}

void ft_do_it(int s, char *c, char *buf)
{
    int k = 0;
    char *str = NULL;

    if (!*c)
        return ;
    str = malloc(sizeof(char) * 3);
    ft_null(str, 3);
    k = (*c - 48) * s;
    ft_itoa(str, k);
    if (str[0] == '\0')
        str[0] = '0';
    ft_sum(buf, str);
    free(str);
    ft_do_it(s, c + 1, buf + 1);
}

void ft_proiz(char *s, char *c, char *str)
{
    char *buf;

    if (*s == '\0' || *s == '-')
        return ;
    buf = malloc(sizeof(char) * 512);
    ft_null(buf, 511);
    *buf = '0';
    ft_do_it(((*s) - 48), c, buf);
    ft_sum(str, buf);
    free(buf);
    ft_proiz(s + 1, c, str + 1);
}

void change_sign(char *s)
{
    if (*s == '-')
        *s = '\0';
    else
        *(s + 1) = '-';
}

void set_sign(char *s, char *c)
{
    if (*s == '-')
        *c = *s;
}

void ft_null_it(char *s)
{
    if (*s == '\0')
        return ;
    *s = '\0';
    ft_null_it(s + 1);
}

void step(char *s, size_t i)
{
   if (i == 0)
     return ;
       s[i] = s[i - 1];
    step(s, --i);
}

void ft_razn(char *s, char *c, size_t i)
{
    char *str;

    if (c[i] == '-')
        i--;
    if (s[i] < c[i])
    {
        if (s[i + 1] == '\0')
        {         
            s[ft_strlen(s)] = '-';            
            return ;
        }
        else
        {
            s[i] = s[i] + 10 - (c[i] - '0');
            if (s[i + 1] != '0')
                s[i + 1] -= 1;
            else
                ft_next_zero(s += i + 1);
            if (s[i + 1] == '0' && s[i + 2] == '\0')
                s[i + 1] = '\0';
            if (s[i + 1] == '0' && s[i + 2] == '-')
            {
                s[i + 1] = '-';
                s[i + 2] = '\0';
            }
        }
    }
    else
    {
        s[i] = s[i] - c[i] + '0';
        if (s[i] == '0' && s[i + 1] == '\0')
            s[i] = '\0';
    }
    if (i == 0)
    {
        if (s[0] == '\0')
            s[0] = '0';
        return ;
    }
    ft_razn(s, c, i - 1);
}

void ft_chast_next(char *s, char *c, char *str, size_t i, size_t k)
{
    ft_razn(s + i - k - 1, c, k);
    if (*(s + ft_strlen(s) - 1) != '-')
    {
       write(1,"!",1);
       ft_putstr(c);
       ft_sum(str, "1");
 //      if (chack_nullis(s) != 0)
       ft_chast_next(s, c, str, i, k);
    }
    else
       {
        ft_putstr(s);
        change_sign(s + ft_strlen(s) - 1);
//        ft_sum(s + i - k, c);
        if (i <= k || *(s + 1) == '\0')    
        return ;
          if (chack_nullis(str + 1) != 0)
          {
           step(str, ft_strlen(str));
           str[0] = '0';
          }
          if (chack_nullis(s) != 0 || *(s + 1) != '\0')
          ft_chast_next(s, c, str, --i, k);
       }
}

void ft_chast(char *s, char *c, char *str, size_t i, size_t k)
{
    if (s[i] == '-')
        i--;
    if (k >= i)
    {
        if (k > i || s[i] < c[k])
        {
            str[0] = '0';
            return ;
        }
    }
    if (chack_nullis(c) == 0)
    {
        str[0] = '0';
        return ;
    }
    ft_chast_next(s, c, str, i, k);
}

void ft_calc(char *res, char **buf)
{
    char *str;

    if (*buf == NULL)
        return ;
    if (**buf == '+')
    {
        *(buf += 1);
        if (**buf == '-')
        {
            *(buf += 1);
            if (*(res + ft_strlen(res) - 1) != '-')
                ft_raz(res, *buf, ft_strlen(buf) - 1);
            else
            {
                change_sign(res + ft_strlen(res) - 1);
                ft_sum(res, *buf);
                *(res + ft_strlen(res)) = '-';
            }
        }
        else if (*(res + ft_strlen(res) - 1) != '-')
            ft_sum(res, *buf);
        else
        {
            *(res + ft_strlen(res) - 1) = '\0';
            ft_raz(res, *buf, ft_strlen(*buf) - 1);
            change_sign(res + ft_strlen(res) - 1);
        }
    }
    else if(**buf == '-')
    {
        *(buf += 1);
        if (*(res + ft_strlen(res) - 1) == '-')
        {
            *(res + ft_strlen(res) - 1) = '\0';
            ft_sum(res, *buf);
            *(res + ft_strlen(res)) = '-';
        }
        else
            ft_raz(res, *buf, ft_strlen(*buf) - 1);
    }
    else if(**buf == '*')
    {
        str = malloc(sizeof(char) * 512);
        ft_null(str, 512);
        *str = '0';
        *(buf += 1);
        if (**buf == '-')
        {
            change_sign(res + ft_strlen(res) - 1);
            *(buf += 1);
        }
        ft_proiz(res,*buf, str);
        set_sign(res + ft_strlen(res) - 1, str + ft_strlen(str));
        if (chack_nullis(str) == 0)
        {
            ft_null_it(res);
            res[0] = '0';
        }
        else
            change(res, str);
        free(str);
    }
    else if (**buf == '/')
    {
        str = malloc(sizeof(char) * 512);
        ft_null(str, 512);
        *str = '0';
        *(buf += 1);
        if (**buf == '-')
        {
            change_sign(res + ft_strlen(res) - 1);
            *(buf += 1);
        }
        ft_chast(res, *buf, str, ft_strlen(res) - 1, ft_strlen(*buf) - 1);
        set_sign(res + ft_strlen(res) - 1, str + ft_strlen(str));
        ft_null_it(res);
        change(res, str);
        free(str);
    }
    *(buf += 1);
    ft_calc(res, buf);
}

void ft_rewind(char *s, char **buf)
{
    char *res;

    res = s + 10;
    if (**buf == '(')
        *(buf += ft_naher_skobki(buf));
    if (**buf == '-')
    {
        *(buf += 1);
        *(res + ft_strlen(*buf)) = '-';
    }
    rerew(res, *buf);
    *(buf += 1);
    ft_calc(res, buf);
    write (1, " = ", 3);
    revstr(res, ft_strlen(res));
}

void ft_erase(char **buf)
{
    char *res;

    if (buf == NULL)
    {
        write(1,"error",5);
        return ;
    }
    if (!(res = malloc(sizeof(char) * 512)))
    {
        ft_free(buf);
        write(1,"error",5);
        return ;
    }
    ft_null(res, 512);
    ft_rewind(res, buf);
    free(res);
}

int main()
{
    char *s;
    int i = 0;
    char **buf;

    while(i >= 0)
    {
        if (!(s =  malloc(sizeof(char) * 512)))
        {
            write(1,"error",5);
            return(0);
        }
        write(1, "your input. q for exit\n", 23);
        i = read(0, s, 512);
        s[i] = '\0';
        if (*s == 'q')
        {
            write(1,"exit\n",5);
            free(s);
            break;
        }
        if (*s != '\0' && *s != '\n' && *s && *s != '+' && *s != '*' && *s != '/'
                && !(*s == '-' && *(s + 1) == '-') && *s != '.'
                &&    check(s) != 0 && skobki(s, 0) != NULL
                && ft_checksign(s) != 0)
        {
            buf = str_split(s);
            free(s);
            ft_erase(buf);
            while(*buf != NULL)
                free(*buf++);
            free(buf);
        }
        else
        {
            free(s);
            write (1,"input is incorrect!\n", 20);
        }
    }
    return 0;
}
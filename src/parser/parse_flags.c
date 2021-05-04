#include "parse_flags.h"
#include <libft.h>

t_flags create_empty_flag()
{
    const t_flags flags = {
        .color = FALSE,
        .verbose = FALSE,
        .file_output = FALSE,
    };

    return (flags);
}

t_flags set_flags(const char *flag)
{
    char cur;
    t_flags flags;

    ++flag;
    cur = *flag;
    flags = create_empty_flag();
    while (cur != '\0')
    {
        if (cur == COLOR)
            flags.color = TRUE;
        else if (cur == VERBOSE)
            flags.verbose = TRUE;
        else if (cur == FILE_OUTPUT)
            flags.file_output = TRUE;
        else
            return (create_empty_flag());
        ++flag;
        cur = *flag;
    }
    return (flags);
}

t_flags parse_flags(int *argc, const char *str[])
{
    const int len = ft_strlen(*str);
    t_flags flag;

    flag = create_empty_flag();
    if (*argc < 2 || *str[0] != '-')
        return (flag);
    if (len < 2 || len > 4)
        return (flag);
    return (set_flags(str[0]));
}

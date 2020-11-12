#include "ush.h"

int main(int argc, char **argv) {
    prompt_colors[1] = MX_RED;
    prompt_colors[0] = MX_GRN;
    prompt_colors[2] = MX_YEL;
    prompt_colors[3] = MX_MAG;
    prompt_colors[4] = MX_CYN;
    prompt_colors[5] = MX_WHT;
    prompt_colors[6] = MX_BOLD_MAGENTA;
    prompt_colors[7] = MX_BOLD_CYAN;
    prompt_color_counter = 0;
    t_shell *m_s = mx_init_shell(argc, argv);

    (void)argc;
    (void)argv;
    mx_ush_loop(m_s);
    return MX_EXIT_SUCCESS;
}

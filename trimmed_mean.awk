{
    sum=$9+$10+$11+$12+$13+$14+$15+$16+$17+$18+$19+$20+$21+$22+$23+$24;

    max = $9;
    sec_max = $9
    min = $9;
    sec_min = $9
    for (i = 10; i < NF; i++) {
        if ($i > sec_max) {
            if ($i > max) {
                sec_max = max;
                max = $i;
            } else {
                sec_max = $i;
            }
        }
        if ($i < sec_min) {
            if ($i < min) {
                sec_min = min;
                min = $i;
            } else {
                sec_min = $i;
            }
        }
    }

    trimmed_mean = ((sum - max - sec_max - min - sec_min) / 12);

    print(trimmed_mean);
}

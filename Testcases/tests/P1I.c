int main() {
   int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;
   int temp1, temp2, temp3, temp4, temp5;
   int result;
   
   a = 2;
   b = 3;
   c = 4;
   d = 5;
   e = 6;
   f = 7;
   g = 8;
   h = 9;
   i = 10;
   j = 11;
   k = 12;
   l = 13;
   m = 14;
   n = 15;
   o = 16;
   p = 17;
   q = 18;
   r = 19;
   s = 20;
   t = 21;
   u = 22;
   v = 23;
   w = 24;
   x = 25;
   y = 26;
   z = 27;
   
   temp1 = a * b + c * d - e * f + g * h - i * j + k * l - m * n + o * p - q * r + s * t - u * v + w * x - y * z;
   temp2 = a + b - c + d - e + f - g + h - i + j - k + l - m + n - o + p - q + r - s + t - u + v - w + x - y + z;
   temp3 = a * b * c / d / e * f * g / h * i * j / k / l * m * n / o * p * q / r / s * t * u / v * w * x / y / z;
   temp4 = a - b - c - d - e - f - g - h - i - j - k - l - m - n - o - p - q - r - s - t - u - v - w - x - y - z;
   temp5 = a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x + y + z;

   printf("%d\n", temp1);
   printf("%d\n", temp2);
   printf("%d\n", temp3);
   printf("%d\n", temp4);
   printf("%d\n", temp5);

   result = temp1 + temp2 - temp3 * temp4 + temp5;
   
   printf("%d\n", result);
   return 0;
}

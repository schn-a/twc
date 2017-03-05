/*
 * Copyright (c) 2017 André Schneider <schn.a@protonmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>

#define UST 19
#define RFB_ABSCHLAG 4

int add_ust(double);
int sub_ust(double);
int rabattfreibetrag(double, double, double);

int main(int argc, char *argv[])
{
  int opt;
  double n; /* TODO: Sinnvollen Namen geben! */
  double listenpreis, arbeitnehmerpreis, jahresfreibetrag;
  char choice_ust, choice_fb;
  while ((opt = getopt(argc, argv, "uf")) != -1 ) {
    switch (opt) {
    case 'u':
      printf("MwSt. [a]ddieren oder [s]ubtrahieren? ");
      scanf("%c", &choice_ust);
      if (choice_ust == 'a') {
        printf("Betrag ohne MwSt. eingaben: ");
        scanf("%lf", &n);
        add_ust(n);
      }
      else if (choice_ust == 's') {
        printf("Betrag mit MwSt. eingaben: ");
        scanf("%lf", &n);
        sub_ust(n);
      }
      else {
        fprintf(stderr, "Ungueltige Auswahl: %c\n", choice_ust);
      }
      break;
    case 'f':
      printf("Freibetrag auswaehlen: [R]abattfreibetrag\n");
      scanf("%c", &choice_fb);
      if (choice_fb == 'R') {
        printf("Listenpreis: ");
        scanf("%lf", &listenpreis);
        printf("Tatsaechlicher Kaufpreis (Arbeitnehmer): ");
        scanf("%lf", &arbeitnehmerpreis);
        printf("Uebriger Jahrefreibetrag (vor Kauf): ");
        scanf("%lf", &jahresfreibetrag);
        rabattfreibetrag(listenpreis, arbeitnehmerpreis, jahresfreibetrag);
      }
        break;
    default:
      fprintf(stderr, "Usage: %s [-fu]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}

int add_ust(double betrag_ohne_ust)
{
  printf("%.2f EUR plus 19%% MwSt. = %.2f EUR\n", betrag_ohne_ust, ((betrag_ohne_ust * (UST + 100)) / 100));
  return 0;
}

int sub_ust(double betrag_mit_ust)
{
  printf("%.2f EUR minus 19%% MwSt. = %.2f EUR\n", betrag_mit_ust, ((betrag_mit_ust * 100) / (UST + 100)));
  return 0;
}

int rabattfreibetrag(double listenpreis, double arbeitnehmerpreis, double jahresfreibetrag)
{
  double abschlag, berichtigterPreis, geldwerterVorteil, stpfl, freibetrag_neu;
  printf("------\n");
  printf("\tListenpreis:\t\t\t %-#7.2f EUR\n", listenpreis);
  abschlag = (listenpreis * RFB_ABSCHLAG) / 100;
  printf("./.\tAbschlag (4%% von Listenpreis):\t %-#7.2f EUR\n", abschlag);
  printf("-------------------------------------------------------\n");
  berichtigterPreis = listenpreis - abschlag;
  printf("=\tberichtiger Abgabepreis:\t %-#7.2f EUR\n", berichtigterPreis);
  printf("./.\tvom AN gezahlter Preis:\t\t %-#7.2f EUR \n", arbeitnehmerpreis);
  printf("-------------------------------------------------------\n");
  geldwerterVorteil = berichtigterPreis - arbeitnehmerpreis;
  printf("=\tgeldwerter Vorteil:\t\t %-#7.2f EUR\n", geldwerterVorteil);
  printf("./.\tRabattfreibetrag:\t\t %-#7.2f EUR\n", jahresfreibetrag);
  printf("-------------------------------------------------------\n");
  stpfl = geldwerterVorteil - jahresfreibetrag;
  printf("=\tsteuerpflichtiger Arbeitslohn:\t %-#7.2f EUR\n", stpfl);

  return 0;
}

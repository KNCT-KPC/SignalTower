#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
void jan(int k,int hoge,int n,int a) {
	printf("\nQ グー   W チョキ　E　パー\n");
	while (1) {
		k = _getch();
		if (k == 'q' || k == 'w' || k == 'e')
			break;
	}

	srand((unsigned)time(NULL));
	hoge = rand() % 100 + 1;
	if (hoge <= 50) {//相手が宣言　//勝ち
		if (k == 'q') {
			printf("\nあなたはグーを出しました。\ncpuはチョキを出しました。\n");
		}
		else if (k == 'w') {
			printf("\nあなたはチョキを出しました。\ncpuはパーを出しました。\n");
		}
		else if (k == 'e') {
			printf("\nあなたはパーを出しました。\ncpuはグーを出しました。\n");
		}
		a = (a + 1);
		printf("\ncpu「ワイの負け」\n\n\n");

	}
	else if (hoge > 50) {//相手が宣言　//負け
		if (k == 'q') {
			printf("\nあなたはグーを出しました。\ncpuはパーを出しました。\n\n");
		}
		else if (k == 'w') {
			printf("\nあなたはチョキを出しました。\ncpuはグーを出しました。\n");
		}
		else if (k == 'e') {
			printf("\nあなたはパーを出しました。\ncpuはチョキを出しました。\n");
		}
		if (k == 'q' || k == 'w' || k == 'e') {
			n = (n + 1);
			printf("\ncpu「わいの勝ち」\n\n\n");
		}
	}
}

int main(void) {
	char k;
	int hoge;
	int j = 1;//じゃんけん回数
	int a = 0;//勝った数
	int n = 0;//負けた数
	int e = 0;//勝率
	int p = 0;//前回負けた数とか
	int o = 0;//リセット
	int h = 0;//ゲームを変える
	int d = 1;//勝率セーブ
	int J = 1;//あっちむいて回数

	
	while (1) {
		if (h == 0) {
			printf("じゃんけん　をしますか　　あっちむいてほい　をしますか\n\nA じゃんけん　　S あっちむいてほい\n");
			while (1) {
				k = _getch();
				if (k == 'a' || k == 's')
					break;
			}
		}
		if (k == 's' || h == 1) {//あっちむいてほい
			while (1) {
				o = 1;
				printf("\n\n\n%d回目のあっちむいてほいです   %d勝%d敗中です\nあなたの勝率%d％\n", J, a, n, e);
				printf("Q グー   W チョキ　E　パー\n\n");
				while (1) {
					k = _getch();
					if (k == 'q' || k == 'w' || k == 'e')
						break;
				}


				srand((unsigned)time(NULL));
				hoge = rand() % 200 + 1;

				if (hoge <= 180) {//じゃんけん負け
					if (k == 'q') {
						printf("あなたはグーを出しました。\ncpuはパーを出しました。\n");
					}
					else if (k == 'w') {
						printf("あなたはチョキを出しました。\ncpuはグーを出しました。\n");
					}
					else if (k == 'e') {
						printf("あなたはパーを出しました。\ncpuはチョキを出しました。\n");
					}
					if (hoge < 10) {//後出し
						while (1) {
							if ((k = getchar()) == '\n')
								break;
						}
						a = a + 1;
						p = 1;
						printf("\n\n\n\n\n本当はcpuが後出しをしました\ncpu「俺の負け...」\n\n\n\n\n");
					}
					if (p != 1) {
						printf("\ncpu「あっち向いて...」\nW 上を向く　　　S 下を向く　　　A 左を向く　　　D 右を向く\n\n");
						while (1) {
							k = _getch();
							if (k == 'w' || k == 's' || k == 'a' || k == 'd')
								break;
						}
						srand((unsigned)time(NULL));
						hoge = rand() % 100 + 1;
						if (hoge < 60) {//あっちむいて負け
							if (k == 'w') {
								printf("\ncpuは上を指しました。\n");
							}
							else if (k == 's') {
								printf("\ncpuは下を指しました。\n");
							}
							else if (k == 'A') {
								printf("\ncpuは左を指しました。\n");
							}
							else if (k == 'd') {
								printf("\ncpuは右を指しました。\n");
							}
							n = (n + 1);
							printf("cpu「俺の勝ち！何で負けたか明日まで（ry」\n\n\n");
						}
						else if (hoge >= 60) {//あっち向いて勝ち
							if (hoge >= 20) {

								if (k == 'w') {
									printf("\ncpuは下を指しました。\n");
								}
								else if (k == 's') {
									printf("\ncpuは左を指しました。\n");
								}
								else if (k == 'A') {
									printf("\ncpuは右を指しました。\n");
								}
								else if (k == 'd') {
									printf("\ncpuは上を指しました。\n");
								}
							}
							else if (hoge >= 40) {//あっち向いて勝ち
								if (k == 'w') {
									printf("\ncpuは左を指しました。\n");
								}
								else if (k == 's') {
									printf("\ncpuは上を指しました。\n");
								}
								else if (k == 'A') {
									printf("\ncpuは下を指しました。\n");
								}
								else if (k == 'd') {
									printf("\ncpuは右を指しました。\n");
								}
							}
							else if (hoge >= 60) {//あっち向いて勝ち
								if (k == 'w') {
									printf("\ncpuは右を指しました。\n");
								}
								else if (k == 's') {
									printf("\ncpuは上を指しました。\n");
								}
								else if (k == 'A') {
									printf("\ncpuは上を指しました。\n");
								}
								else if (k == 'd') {
									printf("\ncpuは下を指しました。\n");
								}
							}
							a = (a + 1);
							printf("cpu「ワイの負け」\n\n\n");
						}
					}

				}
				else if (hoge > 180) {//じゃんけん勝ち

					if (k == 'q') {
						printf("あなたはグーを出しました。\ncpuはチョキを出しました。\n");
					}
					else if (k == 'w') {
						printf("あなたはチョキを出しました。\ncpuはパーを出しました。\n");
					}
					else if (k == 'e') {
						printf("あなたはパーを出しました。\ncpuはグーを出しました。\n");
					}
					printf("\nあなた「あっち向いて...」\nW 上を指す　　　S 下を向指す　　　A 左を指す　　　D 右を指す\n\n");
					while (1) {
						k = _getch();
						if (k == 'w' || k == 's' || k == 'a' || k == 'd')
							break;
					}
					srand((unsigned)time(NULL));
					hoge = rand() % 100 + 1;
					if (hoge <= 30) {//あっちむいて勝ち
						if (k == 'w') {
							printf("\ncpuは上を向きました。\n");
						}
						else if (k == 's') {
							printf("\ncpuは下を向きました。\n");
						}
						else if (k == 'A') {
							printf("\ncpuは左を向きました。\n");
						}
						else if (k == 'd') {
							printf("\ncpuは右を向きました。\n");
						}
						a = (a + 1);
						printf("cpu「ワイの負け」\n\n\n");
					}
					else if (hoge > 30) {//あっち向いて負け
						if (20 > hoge > 10) {
							if (k == 'w') {
								printf("\ncpuは下を向きました。\n");
							}
							else if (k == 's') {
								printf("\ncpuは左を向きました。\n");
							}
							else if (k == 'A') {
								printf("\ncpuは右を向きました。\n");
							}
							else if (k == 'd') {
								printf("\ncpuは上を向きました。\n");
							}
						}
						else if (30 > hoge > 20) {//あっち向いて負け
							if (k == 'w') {
								printf("\ncpuは左を向きました。\n");
							}
							else if (k == 's') {
								printf("\ncpuは上を向きました。\n");
							}
							else if (k == 'A') {
								printf("\ncpuは下を向きました。\n");
							}
							else if (k == 'd') {
								printf("\ncpuは右を向きました。\n");
							}
						}
						else if (hoge > 30) {//あっち向いて負け
							if (k == 'w') {
								printf("\ncpuは右を向きました。\n");
							}
							else if (k == 's') {
								printf("\ncpuは上を向きました。\n");
							}
							else if (k == 'A') {
								printf("\ncpuは上を向きました。\n");
							}
							else if (k == 'd') {
								printf("\ncpuは下を向きました。\n");
							}
						}
						n = (n + 1);
						printf("cpu「俺の勝ち！何で負けたか明日まで（ry」\n\n\n");
					}
				}
				printf("続ける場合は何かキーを押してください...  R 回数をリセット T 最初に戻る\nZ 記録をセーブしてじゃんけんをする\n");
				while (1) {
					k = _getch();
					if (k != 'r' && k != 't' && k != 'z' || k == 'r' || k == 't' || k == 'z')
						break;
				}
				if (k != 'r' && k != 't' && k != 'z') {//続ける
					e = (a * 100) / d;
					J = J + 1;
					d = d + 1;
					p = 0;
				}

				else if (k == 'r') {//リセット
					J = 1;
					d = 1;
					a = 0;
					n = 0;
					e = 0;
					p = 0;
					j = 1;
				}
				else if (k == 't') {//最初に
					printf("\n\n\n");
					J = 1;
					d = 1;
					a = 0;
					n = 0;
					e = 0;
					o = 0;
					p = 0;
					h = 0;
					j = 1;
				}
				else if (k == 'z') {//セーブ
					h = 2;
					o = 0;
					d = d + 1;
					J = J + 1;
				}
				if (o == 0)
					break;
			}
		}

		else if (k == 'a' || h == 2) {//じゃんけん
			while (1) {
				o = 1;
				printf("\n\n\n%d回目のじゃんけんです     %d勝%d敗中です\nあなたの勝率%d％\n", j, a, n, e);
				if (n != p && n % 10 == 0 && n >= 10) {//負けが１０の倍数
					p = n;

					srand((unsigned)time(NULL));
					hoge = rand() % 100 + 1;
					printf("結構負けましたね...\n最初は...\nQ グー   W チョキ　E　パー");
					while (1) {
						k = _getch();
						if (k == 'q' || k == 'w' || k == 'e')
							break;
					}
					printf("\nじゃんけん...\nQ グー   W チョキ　E　パー\n\n");
					while (1) {
						k = _getch();
						if (k == 'q' || k == 'w' || k == 'e')
							break;
					}


					if (hoge <= 20) {//負け
						if (k == 'q') {
							printf("\nあなたはグーを出しました。\ncpuはパーを出しました。\n");
						}
						else if (k == 'w') {
							printf("\nあなたはチョキを出しました。\ncpuはグーを出しました。\n");
						}
						else if (k == 'e') {
							printf("\nあなたはパーを出しました。\ncpuはチョキを出しました。\n");
						}
						n = (n + 1);
						printf("cpu「俺の勝ち！何で負けたか明日まで（ry」\n\n\n");

					}
					else if (hoge > 20) {//勝ち

						if (k == 'q') {
							printf("\nあなたはグーを出しました。\ncpuはチョキを出しました。\n");
						}
						else if (k == 'w') {
							printf("\nあなたはチョキを出しました。\ncpuはパーを出しました。\n");
						}
						else if (k == 'e') {
							printf("\nあなたはパーを出しました。\ncpuはグーを出しました。\n");
						}
						a = (a + 1);
						printf("cpu「やるやん！」\n\n\n");
					}
				}
				else if (n % 10 > 0 || j >= 1) {
					if (j % 5 == 0) {//回数が５の倍数
						srand((unsigned)time(NULL));
						hoge = rand() % 100 + 1;
						printf("最初は...\nQ グー   W チョキ　E　パー\n");
						while (1) {
							k = _getch();
							if (k == 'q' || k == 'w' || k == 'e')
								break;
						}
						if (hoge <= 85) {
							printf("じゃんけん...\nQ グー   W チョキ　E　パー\n");
							while (1) {
								k = _getch();
								if (k == 'q' || k == 'w' || k == 'e')
									break;
							}


							if (hoge <= 57) {//負け
								if (k == 'q') {
									printf("\nあなたはグーを出しました。\ncpuはパーを出しました。\n");
								}
								else if (k == 'w') {
									printf("\nあなたはチョキを出しました。\ncpuはグーを出しました。\n");
								}
								else if (k == 'e') {
									printf("\nあなたはパーを出しました。\ncpuはチョキを出しました。\n");
								}
								n = (n + 1);
								printf("\ncpu「俺の勝ち！何で負けたか明日まで（ry」\n\n\n");
							}
							else if (hoge > 57) {//勝ち

								if (k == 'q') {
									printf("\nあなたはグーを出しました。\ncpuはチョキを出しました。\n");
								}
								else if (k == 'w') {
									printf("\nあなたはチョキを出しました。\ncpuはパーを出しました。\n");
								}
								else if (k == 'e') {
									printf("\nあなたはパーを出しました。\ncpuはグーを出しました。\n");
								}
								a = (a + 1);
								printf("\ncpu「やるやん！」\n\n\n");
							}
						}
						else if (hoge > 85) {//理不尽

							if (k == 'q') {
								printf("\nあなたはグーを出しました。\ncpuはパーを出しました。\n");
							}
							else if (k == 'w') {
								printf("\nあなたはチョキを出しました。\ncpuはグーを出しました。\n");
							}
							else if (k == 'e') {
								printf("\nあなたはパーを出しました。\ncpuはチョキを出しました。\n");
							}
							n = (n + 1);
							printf("\n本だけ☆スケ「俺の勝ち！\n　　　　　　　何で負けたか明日までに考えておいてください。\n　　　　　　　そしたら何かが見えてくるはずです。」\n\n\n");
						}
					}
					else if (j % 5 > 0) {//いつも
						srand((unsigned)time(NULL));
						switch (hoge = rand() % 12 + 1) {

						case 1:
							printf("cpu「私はグーを出します」");
							jan( k, hoge,  n, a);
							break;
						case 2:
							printf("cpu「私はチョキを出します」");
							jan(k, hoge, n, a);
							break;
						case 3:
							printf("cpu「私はパーを出します」");
							jan(k, hoge, n, a);
							break;
						case 4:
							printf("cpu「私はグーを出しません」");
							jan(k, hoge, n, a);
							break;
						case 5:
							printf("cpu「私はチョキを出しません」");
							jan(k, hoge, n, a);
							break;
						case 6:
							printf("cpu「私はパーを出しません」");
							jan(k, hoge, n, a);
							break;


						default:
							printf("Q グー   W チョキ　E　パー\n\n");
							while (1) {
								k = _getch();
								if (k == 'q' || k == 'w' || k == 'e')
									break;
							}


							srand((unsigned)time(NULL));
							hoge = rand() % 100 + 1;

							if (hoge <= 90) {//負け
								if (k == 'q') {
									printf("\nあなたはグーを出しました。\ncpuはパーを出しました。\n");
								}
								else if (k == 'w') {
									printf("\nあなたはチョキを出しました。\ncpuはグーを出しました。\n");
								}
								else if (k == 'e') {
									printf("\nあなたはパーを出しました。\ncpuはチョキを出しました。\n");
								}
								n = (n + 1);
								printf("\ncpu「俺の勝ち！何で負けたか明日まで（ry」\n\n\n");
								if (hoge < 5) {//後出し
									while (1) {
										k = getchar();
										if ((k = getchar()) == '\n')
											break;
									}
									a = (a + 1);
									n = (n - 1);
									printf("\n\n\n\n\n本当はcpuが後出しをしました\ncpu「俺の負け...」\n\n\n\n\n");
								}

							}
							else if (hoge > 90) {//勝ち

								if (k == 'q') {
									printf("\nあなたはグーを出しました。\ncpuはチョキを出しました。\n");
								}
								else if (k == 'w') {
									printf("\nあなたはチョキを出しました。\ncpuはパーを出しました。\n");
								}
								else if (k == 'e') {
									printf("\nあなたはパーを出しました。\ncpuはグーを出しました。\n");
								}
								a = (a + 1);
								printf("\ncpu「やるやん！」\n\n\n");

							}
							break;
						}
					}
				}

				printf("続ける場合は何かキーを押してください...  R 回数をリセット T 最初に戻る\nZ 記録をセーブしてあっちむいてほいをする\n");
				while (1) {
					k = _getch();
					if (k != 'r' && k != 't' || k == 'r' || k == 't' || k == 'z')
						break;
				}
				if (k != 'r' && k != 't' && k != 'z') {//続ける
					e = (a * 100) / d;
					j = j + 1;
					d = d + 1;
				}

				else if (k == 'r') {//リセット
					j = 1;
					d = 1;
					a = 0;
					n = 0;
					e = 0;
					J = 1;
				}
				else if (k == 't') {//最初に
					printf("\n\n\n");
					j = 1;
					d = 1;
					a = 0;
					n = 0;
					e = 0;
					o = 0;
					h = 0;
					J = 1;
				}
				else if (k == 'z') {//セーブ
					h = 1;
					o = 0;
					d = d + 1;
					j = j + 1;
				}
				if (o == 0)
					break;
			}
		}
	}
	return (0);
}

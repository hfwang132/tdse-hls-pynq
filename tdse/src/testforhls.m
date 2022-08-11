% clear; clc;
I = 0.0 + 1.0i;
psi_re_test = load("psi_re.txt");
psi_im_test = load("psi_im.txt");
psi_new_re_test = load("psi_new_re.txt");
psi_new_im_test = load("psi_new_im.txt");
psi_test = abs(psi_re_test + psi_im_test * I);
psi_new_test = abs(psi_new_re_test + psi_new_im_test * I);
V_test = load("potential_test.txt");

[X, Y] = meshgrid(1:100,1:100);
figure(1);
subplot(3,2,1);
surf(X', Y', psi_test);
subplot(3,2,2);
surf(X', Y', psi_new_test);
subplot(3,2,3);
surf(X', Y', abs(psi));
subplot(3,2,4);
surf(X', Y', abs(psi_new));
subplot(3,2,5);
surf(X', Y', V);
subplot(3,2,6);
surf(X', Y', V_test);

diff = psi_new_test - psi_new;
sqrt(sum(sum(abs(diff).^2))/10000)

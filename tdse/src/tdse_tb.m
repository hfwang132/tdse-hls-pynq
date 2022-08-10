% clear; clc;
I = 0.0 + 1.0i;
psi_re_test = load("psi_re.txt");
psi_im_test = load("psi_im.txt");
psi_new_re_test = load("psi_new_re.txt");
psi_new_im_test = load("psi_new_im.txt");
psi_test = abs(psi_re_test + psi_im_test * I);
psi_new_test = abs(psi_new_re_test + psi_new_im_test * I);

[X, Y] = meshgrid(1:100,1:100);
figure(1);
subplot(2,2,1);
surf(X', Y', psi_test);
subplot(2,2,2);
surf(X', Y', psi_new_test);
subplot(2,2,3);
surf(X', Y', abs(psi));
subplot(2,2,4);
surf(X', Y', abs(psi_new));

diff = psi_new_test - psi_new;
sqrt(sum(sum(abs(diff).^2))/10000)

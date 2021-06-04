MAX_LIMITS = 1000;
lda = 4.5;
n = 256

min_value = 1000;
max_value = 1400;

x1 = linspace(min_value, max_value, max_value - min_value + 1);
x2 = linspace(min_value, max_value, MAX_LIMITS);


y1 = poisspdf(x1, n*lda);
y2 = normpdf(x2, n*lda, sqrt(n*lda));

figure

xlabel("n = 1")
bar(x1, y1, 1)
hold on
plot(x2, y2, 'Color', 'r', 'LineWidth', 2)
title(['Comparison Chart with n = ',num2str(n), ', lambda = ', num2str(lda)])

legend('Poisson','CLT')

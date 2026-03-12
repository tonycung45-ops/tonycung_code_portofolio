const cards = document.querySelectorAll('.card');
const form = document.querySelector('.contact-form');

const observer = new IntersectionObserver(entries => {
  entries.forEach(entry => {
    if (entry.isIntersecting) {
      entry.target.classList.add('show');
    }
  });
},{ threshold: 0.3 });

cards.forEach((card, index) => {
  observer.observe(card);
  card.style.transitionDelay = `${index * 0.1}s`;
});

if(form){
  observer.observe(form);
}

const grid = document.querySelector(".portfolio-grid");

document.querySelector(".next").onclick = () => {
  grid.scrollBy({ left: 320, behavior: "smooth" });
};

document.querySelector(".prev").onclick = () => {
  grid.scrollBy({ left: -320, behavior: "smooth" });
};
function article(){
  var title = "Second Coming Of Crypto";
  var blurb = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
  return "<article><h3>"+ title + "</h3><p>" + blurb + "</p><div class='button'><a href='article.html'>View Article</a></div></article>";
}
function addArticle(num, j){
  for(var i = 0; i < num; i++)
    document.getElementsByTagName('section')[j].insertAdjacentHTML('beforeend', article());
}

function bodyLoaded() {
  var category = document.getElementsByClassName("category");
  var num = 1;
  for(var i = 0; i < category.length; i++){
    category[i].addEventListener("click", function(){
      this.classList.toggle("active");
      var content = this.nextElementSibling;
      var img = this.getElementsByTagName("img")[0];
      if(content.style.display === "block"){
        content.style.display = "none";
        img.src = "images/up.png";
      }
      else{ 
        content.style.display = "block";
        img.src = "images/down.png";
        addArticle(3, i);
        console.log(num);
        num = num + 1;
      }
    })
  };
}
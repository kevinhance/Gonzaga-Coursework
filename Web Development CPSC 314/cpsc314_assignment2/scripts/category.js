function bodyLoaded() {
  var category = document.getElementsByClassName("category");
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
      }
    })
  };
}
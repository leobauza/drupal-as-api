test = (function ($, global) {
  if (!$('#site-header').length) { return; }

  var bs = bootstrap,
      custom_fields = {};

  //custom fields
  if (bs.node.custom_fields) {
    console.log('has custom');
    $.each(bs.node.custom_fields, function (k, v) {
      custom_fields[k] = v.safe_value;
    });

  } else {
    console.log('no custom fields');
    var custom_fields = null;
  }

  //log stuff
  console.log(bs);
  console.log(custom_fields);


  //Register partials
  Handlebars.registerPartial('list-item', $('#list-item-partial').html())

  //templetize helper
  function comp(id, context) {
    var source = $(id).html();
    var template = Handlebars.compile(source);
    var html = template(context);

    return html;
  }


  var siteNav = comp('#main-menu',{
    menu: bs.menu.links
  });
  var siteHeader = comp('#site-header',{
    siteName: "My Site's name",
    nodeName: bs.node.title
  });

  var pageBody = comp('#body', {
    body: bs.node.body.safe_value,
    custom_fields: custom_fields
  });

  //console.log(mainNav);
  $('body').append(siteHeader, siteNav, pageBody);


})(jQuery, this);

test2 = (function ($, global) {


  function comp(id, context) {
    var source = $(id).html();
    var template = Handlebars.compile(source);
    var html = template(context);

    return html;
  }

  $('.site__menu').on('click', 'a', function (e) {
    e.preventDefault();

    var $this = $(this),
        data = $this.data(),
        nid = data.nid;

    console.log(nid);

    $.ajax({
      type: "GET",
      url: "/api/node/" + nid,
      success: function (result) {

        //custom fields
        if (result.custom_fields) {
          console.log('has custom');
          $.each(result.custom_fields, function (k, v) {
            result.custom_fields[k] = v.safe_value;
          });

        } else {
          console.log('no custom fields');
          var custom_fields = null;
        }

        var pageBody = comp('#body', {
          body: result.body.safe_value,
          custom_fields: result.custom_fields
        });

        $('.main__body').addClass('to-remove').after(pageBody);
        $('.to-remove').remove();


        console.log(result);
      }
    });


  });

})(jQuery, this);
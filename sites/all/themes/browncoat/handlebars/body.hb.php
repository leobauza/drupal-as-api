<section class="main__body">
  {{{body}}}
  {{#each custom_fields}}
    <p><strong>{{@key}}:</strong> {{this}}</p>
    {{else}}
    <p>no custom fields</p>
  {{/each}}

  <h3>Articles (from view):</h3>
  {{#each articles}}
    <h5>{{this.node_title}}</h5>
    <p>{{{this.field_body.[0].raw.safe_value}}}</p>
    <a href="{{this.alias}}">link...</a>
  {{/each}}

  <h3>Philsophy Slider? (from block):</h3>
  <p>{{philosophy_slider.research_title}}</p>
  <p>{{philosophy_slider.research_body}}</p>
  <p>{{philosophy_slider.simplify_title}}</p>
  <p>{{philosophy_slider.simplify_body}}</p>

</section>
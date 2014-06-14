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
    {{{this.field_body.[0].raw.safe_value}}}
  {{/each}}

</section>